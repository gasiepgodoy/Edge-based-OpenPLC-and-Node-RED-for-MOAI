# -*- coding: utf-8 -*-

import logging
import pika
import json
import psutil

from .topics import MoleculerTopics
from pika.channel import Channel
from pika.adapters.select_connection import SelectConnection
from .consumer import MoleculerConsumer

LOG_FORMAT = ('%(levelname) -10s %(asctime)s %(name) -30s %(funcName) '
                '-35s %(lineno) -5d: %(message)s')
LOGGER = logging.getLogger(__name__)


class MoleculerNode(object):
    """

    If RabbitMQ closes the connection, it will reopen it. You should
    look at the output, as there are limited reasons why the connection may
    be closed, which usually are tied to permission related issues or
    socket timeouts.

    """

    EXCHANGE_TYPE = 'fanout'
    NODE_ID = 'python-node-1'
    HEARTBEAT_INTERVAL = 5

    def __init__(self, amqp_url, node_id=None, namespace=None):
        """Setup the example publisher object, passing in the URL we will use
        to connect to RabbitMQ.

        :param str amqp_url: The URL for connecting to RabbitMQ

        """
        self._connection = None
        self.channel: Channel = None

        self._deliveries = None
        self._acked = None
        self._nacked = None
        self._message_number = None

        self._stopping = False
        self._url = amqp_url
        self.ready_topics = []
        self.expect_topics_count = None
        self.ready_bindings = []
        self.expect_bindings_count = None

        if node_id is not None:
            self.NODE_ID = node_id

        self.namespace = namespace

        self.moleculer_topics = MoleculerTopics(self.NODE_ID, namespace=self.namespace)
        self.consumer = MoleculerConsumer(self.NODE_ID, moleculer_topics=self.moleculer_topics,
                                          namespace=self.namespace)

    def connect(self):
        """This method connects to RabbitMQ, returning the connection handle.
        When the connection is established, the on_connection_open method
        will be invoked by pika. If you want the reconnection to work, make
        sure you set stop_ioloop_on_close to False, which is not the default
        behavior of this adapter.

        :rtype: pika.SelectConnection

        """
        LOGGER.info('Connecting to %s', self._url)
        return pika.SelectConnection(pika.URLParameters(self._url),
                                     on_open_callback=self.on_connection_open,
                                     on_close_callback=self.on_connection_closed,
                                     stop_ioloop_on_close=False)

    def on_connection_open(self, unused_connection):
        LOGGER.info('Connection opened')
        self.open_channel()

    def on_connection_closed(self, connection, reply_code, reply_text):
        """This method is invoked by pika when the connection to RabbitMQ is
        closed unexpectedly. Since it is unexpected, we will reconnect to
        RabbitMQ if it disconnects.

        :param pika.connection.Connection connection: The closed connection obj
        :param int reply_code: The server provided reply_code if given
        :param str reply_text: The server provided reply_text if given

        """
        self.channel = None
        if self._stopping:
            self._connection.ioloop.stop()
        else:
            LOGGER.warning('Connection closed, reopening in 5 seconds: (%s) %s',
                           reply_code, reply_text)
            self._connection.add_timeout(5, self._connection.ioloop.stop)

    def open_channel(self):
        LOGGER.info('Creating a new channel')
        self._connection.channel(on_open_callback=self.on_channel_open)

    def on_channel_open(self, channel):
        LOGGER.info('Channel opened')
        self.channel: Channel = channel
        # self._channel.basic_qos(prefetch_count=1)  # TODO: figure out why prefetch must be disabled to make it work
        # self._channel.confirm_delivery()  # Enabled delivery confirmations
        self.add_on_channel_close_callback()
        self.create_topics()
        self._connection.add_timeout(0.2, self.subscribe_to_topics)
        self._connection.add_timeout(1, self.start_heartbeating)

    def start_heartbeating(self):
        heartbeat_packet = {
            'ver': '2',
            'sender': self.NODE_ID,
            'cpu': psutil.cpu_percent(interval=None)
        }
        self.channel.basic_publish(self.moleculer_topics.exchanges['HEARTBEAT'], '',
                                   json.dumps(heartbeat_packet))
        self._connection.add_timeout(self.HEARTBEAT_INTERVAL, self.start_heartbeating)

    def subscribe_to_topics(self):
        if self.is_bindings_ready:
            self.add_on_cancel_callback()
            # for queue in self.moleculer_topics.queues.values():
            self.channel.basic_consume(self.consumer.discover, self.moleculer_topics.queues['DISCOVER'])
            self.channel.basic_consume(self.consumer.info, self.moleculer_topics.queues['INFO'])
            self.channel.basic_consume(self.consumer.ping, self.moleculer_topics.queues['PING'])
            self.channel.basic_consume(self.consumer.request, self.moleculer_topics.queues['REQUEST'])
            self.channel.basic_consume(self.consumer.response, self.moleculer_topics.queues['RESPONSE'])
            self.channel.basic_consume(self.consumer.event, self.moleculer_topics.queues['EVENT'], no_ack=True)

            for queue_name in self.moleculer_topics.action_queues:
                self.channel.basic_consume(self.consumer.request, queue_name)
            for queue_name in self.moleculer_topics.event_queues:
                self.channel.basic_consume(self.consumer.event, queue_name, no_ack=True)

            self._connection.add_timeout(0.5, self.discover_packet)
        else:
            self._connection.add_timeout(0.1, self.subscribe_to_topics)

    def create_topics(self):
        queues = self.moleculer_topics.queues.items()
        action_queues, events_queues = self.moleculer_topics.action_queues, self.moleculer_topics.event_queues
        self.expect_topics_count = len(queues) + len(self.moleculer_topics.exchanges) + len(action_queues) + len(
            events_queues)

        for queue_type, queue_name in queues:
            if queue_type in ('REQUEST', 'RESPONSE'):
                self.setup_queue(queue_name, ttl=False, exclusive=False)
            elif queue_type == 'HEARTBEAT':
                self.setup_queue(queue_name, ttl=False, exclusive=True)
            else:
                self.setup_queue(queue_name, ttl=True, exclusive=False)

        for queue_name in action_queues:
            self.setup_queue(queue_name, ttl=False, exclusive=False, durable=False)

        for queue_name in events_queues:
            self.setup_queue(queue_name, ttl=True, exclusive=False)

        for exchange_type, exchange_name in self.moleculer_topics.exchanges.items():
            self.setup_exchange(exchange_name)

        self._connection.add_timeout(0.1, self.check_topics_status)

    def check_topics_status(self):
        if len(self.ready_topics) == self.expect_topics_count:
            LOGGER.info('All topics successfully declared')
            self.bind_queues_to_exchanges()
        else:
            self._connection.add_timeout(0.1, self.check_topics_status)

    @property
    def is_bindings_ready(self):
        if len(self.ready_bindings) == self.expect_bindings_count:
            LOGGER.info('All bindings successfully declared.')
            return True
        else:
            return False

    def bind_queues_to_exchanges(self):
        self.expect_bindings_count = len(self.moleculer_topics.bindings)
        for queue_name, fanout_name in self.moleculer_topics.bindings.items():
            self.channel.queue_bind(self.on_bindok, queue_name, fanout_name)

    def add_on_channel_close_callback(self):
        """This method tells pika to call the on_channel_closed method if
        RabbitMQ unexpectedly closes the channel.

        """
        LOGGER.info('Adding channel close callback')
        self.channel.add_on_close_callback(self.on_channel_closed)

    def discover_packet(self):
        req = {
            'ver': '2',
            'sender': self.NODE_ID
        }
        self.channel.basic_publish(self.moleculer_topics.exchanges['DISCOVER'], '', json.dumps(req))

    def on_channel_closed(self, channel, reply_code, reply_text):
        """Invoked by pika when RabbitMQ unexpectedly closes the channel.
        Channels are usually closed if you attempt to do something that
        violates the protocol, such as re-declare an exchange or queue with
        different parameters. In this case, we'll close the connection
        to shutdown the object.

        :param pika.channel.Channel channel: The closed channel
        :param int reply_code: The numeric reason the channel was closed
        :param str reply_text: The text reason the channel was closed

        """
        LOGGER.warning('Channel was closed: (%s) %s', reply_code, reply_text)
        self.channel = None
        if not self._stopping:
            self._connection.close()

    def setup_exchange(self, exchange_name):
        """Setup the exchange on RabbitMQ by invoking the Exchange.Declare RPC
        command. When it is complete, the on_exchange_declareok method will
        be invoked by pika.

        :param str|unicode exchange_name: The name of the exchange to declare

        """
        LOGGER.info('Declaring exchange %s', exchange_name)
        self.channel.exchange_declare(self.on_exchange_declareok,
                                      exchange_name,
                                      self.EXCHANGE_TYPE, durable=True)

    def on_exchange_declareok(self, unused_frame):
        """Invoked by pika when RabbitMQ has finished the Exchange.Declare RPC
        command.

        :param pika.Frame.Method unused_frame: Exchange.DeclareOk response frame

        """
        LOGGER.info('Exchange declared')
        self.ready_topics.append(None)

    def setup_queue(self, queue_name, ttl=True, exclusive=False, durable=False):
        """Setup the queue on RabbitMQ by invoking the Queue.Declare RPC
        command. When it is complete, the on_queue_declareok method will
        be invoked by pika.

        :param auto_delete:
        :param ttl:
        :param str|unicode queue_name: The name of the queue to declare.

        """
        LOGGER.info('Declaring queue %s', queue_name)
        arguments = {}
        if ttl:
            arguments['x-message-ttl'] = 5000  # eventTimeToLive: https://github.com/ice-services/moleculer/pull/72
        self.channel.queue_declare(self.on_queue_declareok, queue_name,
                                   exclusive=exclusive, durable=durable, arguments=arguments)

    def on_queue_declareok(self, method_frame):
        """Method invoked by pika when the Queue.Declare RPC call made in
        setup_queue has completed. In this method we will bind the queue
        and exchange together with the routing key by issuing the Queue.Bind
        RPC command. When this command is complete, the on_bindok method will
        be invoked by pika.

        :param pika.frame.Method method_frame: The Queue.DeclareOk frame

        """
        LOGGER.info('Queue for moleculer declared')
        self.ready_topics.append(None)

    def on_bindok(self, unused_frame):
        """This method is invoked by pika when it receives the Queue.BindOk
        response from RabbitMQ. Since we know we're now setup and bound, it's
        time to start publishing."""
        LOGGER.info('Queue bound to exchange.')
        self.ready_bindings.append(None)

    def add_on_cancel_callback(self):
        """Add a callback that will be invoked if RabbitMQ cancels the consumer
        for some reason. If RabbitMQ does cancel the consumer,
        on_consumer_cancelled will be invoked by pika.

        """
        LOGGER.info('Adding consumer cancellation callback')
        self.channel.add_on_cancel_callback(self.on_consumer_cancelled)

    def on_consumer_cancelled(self, method_frame):
        """Invoked by pika when RabbitMQ sends a Basic.Cancel for a consumer
        receiving messages.

        :param pika.frame.Method method_frame: The Basic.Cancel frame

        """
        LOGGER.info('Consumer was cancelled remotely, shutting down: %r',
                    method_frame)
        if self.channel:
            self.channel.close()

    def run(self):
        """Run the service code by connecting and then starting the IOLoop.

        """
        while not self._stopping:
            self._connection = None
            self._deliveries = []
            self._acked = 0
            self._nacked = 0
            self._message_number = 0

            try:
                self._connection: SelectConnection = self.connect()
                self._connection.ioloop.start()
            except KeyboardInterrupt:
                self.stop()
                if (self._connection is not None and
                        not self._connection.is_closed):
                    self._connection.ioloop.start()

        LOGGER.info('Stopped')

    def stop(self):
        """Stop the example by closing the channel and connection. We
        set a flag here so that we stop scheduling new messages to be
        published. The IOLoop is started because this method is
        invoked by the Try/Catch below when KeyboardInterrupt is caught.
        Starting the IOLoop again will allow the publisher to cleanly
        disconnect from RabbitMQ.

        """
        LOGGER.info('Stopping')
        disconnect_packet = {
            'ver': '2',
            'sender': self.NODE_ID
        }
        self.channel.basic_publish(self.moleculer_topics.exchanges['DISCONNECT'], '',
                                   json.dumps(disconnect_packet))
        self._stopping = True
        self.close_channel()
        self.close_connection()

    def close_channel(self):
        """Invoke this command to close the channel with RabbitMQ by sending
        the Channel.Close RPC command.

        """
        if self.channel is not None:
            LOGGER.info('Closing the channel')
            self.channel.close()

    def close_connection(self):
        """This method closes the connection to RabbitMQ."""
        if self._connection is not None:
            LOGGER.info('Closing connection')
            self._connection.close()
