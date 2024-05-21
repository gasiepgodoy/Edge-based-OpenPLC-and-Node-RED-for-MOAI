// Global Variables Definition// 

const { BAD_MSG } = require('nats')
n_elem = 10 /* The lenght of the array. */ 

PID_param_set = 0  /*The PID parameters set*/
let var_error                  = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let var_integrative            = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let var_time                   = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let var_mv                     = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let sp                         = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let daqpv                      = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
let kp_id                      = Array.from(Array(n_elem).keys()) /*tuple or array of "n_elem" elements */
let ti_id                      = Array.from(Array(n_elem).keys()) /*tuple or array of "n_elem" elements */
let td_id                      = Array.from(Array(n_elem).keys()) /*tuple or array of "n_elem" elements */
//let setpoint                   = Array.from(Array(n_elem).keys()) /*tuple or array of "n_elem" elements */
//let error                      = Array.from(Array(n_elem).keys()) /*tuple or array of "n_elem" elements */

let firstscan                  = Array.from({length: n_elem}, (v, k) => k*0); /*tuple or array of "n_elem" zeroes elements */
//file_descriptor = 0
//prevlogfilename = 0
chout = 0



module.exports = function (RED) {
    "use strict";
    const { ServiceBroker } = require('moleculer')
    let brokers = {}
    RED.events.on('nodes-stopped', async (event) => {
        for (let prop in brokers) {
            await brokers[prop]['broker'].stop()
        }
    })

    RED.events.on('nodes-started', async (event) => {
        if (brokers !== "") {
            for (let i in brokers) {
                for (let j in brokers[i]['services']) {
                    let service = {
                        name: brokers[i]['services'][j]['name'],
                        events: brokers[i]['services'][j]['events'],
                        actions: brokers[i]['services'][j]['actions']
                    }
                    if (brokers[i]['services'][j]['version'] !== "") {
                        service['version'] = brokers[i]['services'][j]['version']
                    }
                    brokers[i]['broker'].createService(service);
                }
                await brokers[i]['broker'].start()
            }
        }
    })

    //MoleculerConfigNode  data input filds//
    function MoleculerConfigNode(n) {
        RED.nodes.createNode(this, n);
        this.name = n.name;
        this.options = n.options;
        this.optionsType = n.optionsType;
        let node = this
        let options = {}
        try {
            if (node.optionsType) {
                options = RED.util.evaluateNodeProperty(node.options, node.optionsType, node)
            } else {
                options = JSON.parse(node.options)
            }
        } catch (e) {
            options = {}
        }
        brokers[node.name] = { broker: null, services: {}, options }
        brokers[node.name]['broker'] = new ServiceBroker(brokers[node.name]['options']);
        node.on('close', async (done) => {
            await brokers[node.name]['broker'].stop()
            done()
        })
    }
    RED.nodes.registerType("moleculer-config", MoleculerConfigNode);

     //MoleculerServiceConfigNode  data input filds//
    function MoleculerServiceConfigNode(n) {
        RED.nodes.createNode(this, n);
        this.name = n.name;
        this.version = n.version;
        this.settingsType = n.settingsType;
        this.settings = n.settings;

        let node = this
        node.on('close', (done) => {
            done()
        })
    }
    RED.nodes.registerType("moleculer-service-config", MoleculerServiceConfigNode);

     //eventNode  data input filds//
    function eventNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.service = RED.nodes.getNode(n.service);
        this.name = n.name;
        this.topic = n.topic;
        this.group = n.group;
        let node = this
        createEvent(node)
    }
    RED.nodes.registerType("moleculer-event", eventNode);

    //emitNode  data input filds//
    function emitNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.broadcast = n.broadcast;
        this.group = n.group;
        var node = this
        createEmit(node);
    }
    RED.nodes.registerType("moleculer-emit", emitNode);

    //callNode  data input filds//
    function callNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        var node = this
        createCall(node);
    }
    RED.nodes.registerType("moleculer-call", callNode);

    // PID4 data input filds//
    function PID4Node(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;

        this.ident = n.ident
        this.kp = n.kp    /* This is where the input data is manipulated  */
        this.ti = n.ti
        this.td = n.td
        this.sp = n.setpoint
        this.spdyn = n.spdyn /*My dynamic sp in*/
        this.pv = n.pv
        
        var node = this
        createPID4(node);
    }
    RED.nodes.registerType("moleculer-PID4", PID4Node);

    //DAQ_AI_I data input filds//
    function Call_DAQ_AI_I(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topicident;
        this.options = n.options;
        this.stack = n.stack;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.pv = n.pv
        var node = this
        createDAQ_AI_I(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AI_I", Call_DAQ_AI_I);

     //DAQ_AI_U data input filds//
     function Call_DAQ_AI_U(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.stack = n.stack;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.pv = n.pv
        var node = this
        createDAQ_AI_U(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AI_U", Call_DAQ_AI_U);

    //DAQ_DI_OPTO data input filds//
    function Call_DAQ_DI_OPTO(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.stack = n.stack;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.pv = n.pv
        var node = this
        createDAQ_DI_OPTO(node);
        }
    RED.nodes.registerType("moleculer-DAQ_DI_OPTO", Call_DAQ_DI_OPTO);

    //DAQ_AO_I_RD data input filds//
    function Call_DAQ_AO_I_RD (n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.stack = n.stack;
        this.pv = n.pv
        var node = this
        createDAQ_AO_I_RD(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_I_RD", Call_DAQ_AO_I_RD);

    //DAQ_AO_U_RD data input filds//
    function Call_DAQ_AO_U_RD(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.stack = n.stack;
        this.pv = n.pv
        var node = this
        createDAQ_AO_U_RD(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_U_RD", Call_DAQ_AO_U_RD);

     //DAQ_AO_OD_RD data input filds//
     function Call_DAQ_AO_OD_RD (n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.stack = n.stack;
        this.pv = n.pv
        var node = this
        createDAQ_AO_OD_RD(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_OD_RD", Call_DAQ_AO_OD_RD);

    //DAQ_AO_U_WT data input filds //
    function DAQ_AO_U_WTNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.stack = n.stack;
        this.out = n.out
        this.mv = n.mv
        this.enable = n.enable
                
        var node = this
        createDAQ_AO_U_WT(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_U_WT", DAQ_AO_U_WTNode);

     //DAQ_AO_I_WT data input filds //
     function DAQ_AO_I_WTNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.out = n.out
        this.mv = n.mv
        this.enable = n.enable
        this.stack = n.stack;
                
        var node = this
        createDAQ_AO_I_WT(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_I_WT", DAQ_AO_I_WTNode);

     //DAQ_AO_OD_WT data input filds //
     function DAQ_AO_OD_WTNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.name = n.name;
        this.topic = n.topic;
        this.options = n.options;
        this.optionsType = n.optionsType;
        
        this.ident = n.ident
        this.out = n.out
        this.mv = n.mv
        this.enable = n.enable
        this.stack = n.stack;
                
        var node = this
        createDAQ_AO_OD_WT(node);
        }
    RED.nodes.registerType("moleculer-DAQ_AO_OD_WT", DAQ_AO_OD_WTNode);

    //reqActionNode  data input filds//
    function reqActionNode(n) {
        RED.nodes.createNode(this, n);
        this.broker = RED.nodes.getNode(n.broker);
        this.service = RED.nodes.getNode(n.service);
        this.name = n.name;
        this.topic = n.topic;
        var node = this
        createAction(node);
    }
    RED.nodes.registerType("moleculer-request-action", reqActionNode);

     //resActionNode  data input filds//
    function resActionNode(n) {
        RED.nodes.createNode(this, n);
        this.name = n.name;
        this.topic = n.topic;
        var node = this
        responseAction(node);
    }
    RED.nodes.registerType("moleculer-response-action", resActionNode);

    //beging getBroker//
    function getBroker(config) {
        if (config && config['name'] !== undefined) {
            if (brokers[config.name] !== undefined) {
                return brokers[config.name]
            } else {
                brokers[config.name] = { broker: null, services: {}, options: RED.util.evaluateNodeProperty(config.options, config.optionsType, config) }
                return brokers[config.name]
            }
        } else {
            throw new Error('Missing Broker Config')
        }
    }

    //beging getService//
    function getService(node) {
        if (node) {
            return node.version + '.' + node.name
        } else {
            throw new Error('Missing Service Config')
        }
    }
    
    //beging createEvent//
    function createEvent(node) {
        let broker = getBroker(node.broker)
        let serviceName = getService(node.service)
        if (!broker['services'].hasOwnProperty(serviceName)) {
            broker['services'][serviceName] = {}
        }
        broker['services'][serviceName]['name'] = node.service.name;
        broker['services'][serviceName]['version'] = node.service.version;
        try {
            if (node.service.settingsType) {
                broker['services'][serviceName]['settings'] = RED.util.evaluateNodeProperty(node.service.settings, node.service.settingsType, node)
            } else {
                broker['services'][serviceName]['settings'] = JSON.parse(node.service.settings)
            }
        } catch (e) {
            broker['services'][serviceName]['settings'] = {}
        }
        if (!broker['services'][serviceName].hasOwnProperty('events')) {
            broker['services'][serviceName]['events'] = {}
        }
        broker['services'][serviceName]['events'][node.topic] = {
            handler: (payload, sender, event) => {
                let msg = { topic: node.topic, payload, sender, event }
                node.status({ fill: 'blue', shape: 'dot', text: 'receiving event...' })
                setTimeout(() => { node.status({}) }, 500)
                node.send(msg)
            }
        }
        if (node.group !== "") {
            broker['services'][serviceName]['events'][node.topic]['group'] = node.group.split(',')
        }
    }

    //beging createEmit//
    function createEmit(node) {
        let broker = getBroker(node.broker)
        node.on('input', (msg) => {

            let topic = msg.topic || node.topic || null
            let group = msg.group || node.group
            let bcast = msg.broadcast || node.broadcast

            let func = 'emit'
            let status = 'emitting...'
            if (bcast) {
                func = 'broadcast'
                status = 'broadcasting...'
            }
            let groups = null
            if (group !== "") {
                groups = group.split(',')
            }
            if (topic) {
                node.status({ fill: 'blue', shape: 'dot', text: status })
                broker['broker'][func](topic, msg.payload, groups)
                setTimeout(() => { node.status({}) }, 500)
            } else {
                node.error('Missing topic, please send topic on msg.topic or Node Topic.', msg)
            }
        })
    }

   //beging createCall//
    function createCall(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {

                let action = msg.action || node.topic
                let options = msg.options || {}
                
                if (options === "" && node.optionsType) {
                    options = RED.util.evaluateNodeProperty(node.options, node.optionsType, node, msg)
                } else {
                    if (options === "") {
                        try {
                            options = JSON.parse(node.options)
                        } catch (e) {
                            options = {}
                        }
                    }
                }
                if (action !== "") {
                    node.status({ fill: 'blue', shape: 'dot', text: 'requesting...' })
                    let res = await broker['broker'].call(action, msg.payload, options)
                    msg.payload = res
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg)
                } else {
                    node.error('Missing action, please send action on msg.action or Node Action.', msg)
                }
            } catch (e) {
                node.status({ fill: 'red', shape: 'ring', text: 'error' })
                node.error(e, msg)
                setTimeout(() => { node.status({}) }, 500)
            }
        })
    }

    //beging createDAQ_AI_I//
    function createDAQ_AI_I(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv  
                let stack = node.stack           
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do createDAQ_AI_I // 
                     node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let daqpv = 0
                    let stackout = 0
                    if (pvtag === "Channel_1")   {daqpv = 1 ; } else { ; }
                    if (pvtag === "Channel_2")   {daqpv = 2 ; } else { ; }
                    if (pvtag === "Channel_3")   {daqpv = 3 ; } else { ; }
                    if (pvtag === "Channel_4")   {daqpv = 4 ; } else { ; }

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    //let res = await broker['broker'].call("daq.riin", {}, {} )
                    let res2 = await broker['broker'].call("megaind-rpi-v8.getInputCurrent", {"stack": stackout, "channel": daqpv})
                   
                    msg.payload = res2
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 

                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 
    
    //beging createDAQ_AI_U//
    function createDAQ_AI_U(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv 
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do DAQ_AI_U // 
                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let daqpv = 0
                    let stackout = 0
                    if (pvtag === "channel_1")   {daqpv = 1 ; } else { ; }
                    if (pvtag === "channel_2")   {daqpv = 2 ; } else { ; }
                    if (pvtag === "channel_3")   {daqpv = 3 ; } else { ; }
                    if (pvtag === "channel_4")   {daqpv = 4 ; } else { ; }

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    //let res = await broker['broker'].call("daq.ruin", {}, {} )
                    let res3 = await broker['broker'].call("megaind-rpi-v8.getInputVoltage", {"stack": stackout, "channel": daqpv})
                   
                    msg.payload = res3
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 
                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 

    //beging createDAQ_DI_OPTO//
    function createDAQ_DI_OPTO(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv 
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do DAQ_DI_OPTO // 
                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let daqpv = 0
                    let stackout = 0
                    if (pvtag === "channel_1")   {daqpv = 1 ; } else { ; }
                    if (pvtag === "channel_2")   {daqpv = 2 ; } else { ; }
                    if (pvtag === "channel_3")   {daqpv = 3 ; } else { ; }
                    if (pvtag === "channel_4")   {daqpv = 4 ; } else { ; }

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    //let res = await broker['broker'].call("daq.ruin", {}, {} )
                    let res3 = await broker['broker'].call("megaind-rpi-v8.getInputOpto", {"stack": stackout, "channel": daqpv})
                   
                    msg.payload = res3
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 
                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 
    
    //beging createDAQ_AO_I_RD//
    function createDAQ_AO_I_RD(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do createDAQ_AO_I_RD // 
                     node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let chout = 0
                    let stackout = 0
                    if (pvtag === "channel_1")   {chout = 1 ; } else { ; }
                    if (pvtag === "channel_2")   {chout = 2 ; } else { ; }
                    if (pvtag === "channel_3")   {chout = 3 ; } else { ; }
                    if (pvtag === "channel_4")   {chout = 4 ; } else { ; }
                    
                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }
            

                    //let res = await broker['broker'].call("daq.riin", {}, {} )
                    let res4 = await broker['broker'].call("megaind-rpi-v8.getOutputCurrent", {"stack": stackout, "channel": chout})
                   
                    msg.payload = res4
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 

                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 

    //beging createDAQ_AO_U_RD//
    function createDAQ_AO_U_RD(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv 
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do createDAQ_AO_U_RD // 
                     node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let chout = 0
                    let stackout = 0
                    if (pvtag === "channel_1")   {chout = 1 ; } else { ; }
                    if (pvtag === "channel_2")   {chout = 2 ; } else { ; }
                    if (pvtag === "channel_3")   {chout = 3 ; } else { ; }
                    if (pvtag === "channel_4")   {chout = 4 ; } else { ; }

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    //let res = await broker['broker'].call("daq.riin", {}, {} )
                    let res9 = await broker['broker'].call("megaind-rpi-v8.getOutputVoltage", {"stack": stackout, "channel": chout})
                   
                    msg.payload = res9
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 

                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 

     //beging createDAQ_AO_OD_RD//
     function createDAQ_AO_OD_RD(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */           
                let options = msg.options || {}                     
                let ident = Number(node.ident)          
                let pvtag       = node.pv 
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) {    
                    // Chamada do createDAQ_AO_OD_RD // 
                     node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  pvtag}) 
                    //console.log(broker['broker'])
                    let chout = 0
                    let stackout = 0
                    if (pvtag === "channel_1")   {chout = 1 ; } else { ; }
                    if (pvtag === "channel_2")   {chout = 2 ; } else { ; }
                    if (pvtag === "channel_3")   {chout = 3 ; } else { ; }
                    if (pvtag === "channel_4")   {chout = 4 ; } else { ; }

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    //let res = await broker['broker'].call("daq.riin", {}, {} )
                    let res9 = await broker['broker'].call("megaind-rpi-v8.getOutputOpenDrain", {"stack": stackout, "channel": chout})
                   
                    msg.payload = res9
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 

                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })  
            } 

    //beging createDAQ_AO_U_WT//
    function createDAQ_AO_U_WT(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action          
                let options = msg.options || {}                      
                let ident = Number(node.ident)          
                let outtag = node.out
                let mv = Number(msg.mv) 
                let stack = node.stack            
                let enable = Number(msg.enable)            
                if (enable === 1) { 
                    let stackout = 0 
                    let chout = 0
                    if (outtag === "Channel_1") { chout = 1  ; } else { ; } /*TQ1*/
                    if (outtag === "Channel_2") { chout = 2  ; } else { ; } /*R01*/
                    if (outtag === "Channel_3") { chout = 3  ; } else { ; } 
                    if (outtag === "Channel_4") { chout = 4  ; } else { ; } 

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }
                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  mv}) 
    
                    let res5 = await broker['broker'].call("megaind-rpi-v8.setOutputVoltage", { "stack": stackout, "channel": chout, "value": mv }, {} )
                    msg.payload = mv
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 
                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })   
            } 

     //beging createDAQ_AO_I_WT//
     function createDAQ_AO_I_WT(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action          
                let options = msg.options || {}                      
                let ident = Number(node.ident)          
                let outtag = node.out
                let mv = Number(msg.mv)
                let stack = node.stack             
                let enable = Number(msg.enable)            
                if (enable === 1) {
                   let stackout = 0 
                   let chout = 0
                    if (outtag === "channel_1") { chout = 1  ; } else { ; } /*TQ1*/
                    if (outtag === "channel_2") { chout = 2  ; } else { ; } /*R01*/
                    if (outtag === "channel_3") { chout = 3  ; } else { ; } 
                    if (outtag === "channel_4") { chout = 4  ; } else { ; } 

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  mv}) 
                    //console.log("Channel out is: " + chout + "  " + outtag + "  " + mv)
                    //let res6 = await broker['broker'].call("daq.wuout", { "channel": chout, "value": mv  }, {} )
                    let res6 = await broker['broker'].call("megaind-rpi-v8.setOutputCurrent", { "stack": stackout, "channel": chout, "value": mv }, {} )
                    msg.payload = res6
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 
                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })   
            } 

    //beging createDAQ_AO_OD_WT//
    function createDAQ_AO_OD_WT(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action          
                let options = msg.options || {}                      
                let ident = Number(node.ident)          
                let outtag = node.out
                let mv = Number(msg.mv)
                let stack = node.stack             
                let enable = Number(msg.enable)            
                if (enable === 1) {
                   let stackout = 0 
                   let chout = 0
                    if (outtag === "channel_1") { chout = 1  ; } else { ; } /*TQ1*/
                    if (outtag === "channel_2") { chout = 2  ; } else { ; } /*R01*/
                    if (outtag === "channel_3") { chout = 3  ; } else { ; } 
                    if (outtag === "channel_4") { chout = 4  ; } else { ; } 

                    if (stack === "0")   {stackout = 0 ; } else { ; }
                    if (stack === "1")   {stackout = 1 ; } else { ; }
                    if (stack === "2")   {stackout = 2 ; } else { ; }
                    if (stack === "3")   {stackout = 3 ; } else { ; }
                    if (stack === "4")   {stackout = 4 ; } else { ; }
                    if (stack === "5")   {stackout = 5 ; } else { ; }
                    if (stack === "6")   {stackout = 6 ; } else { ; }
                    if (stack === "7")   {stackout = 7 ; } else { ; }

                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  mv}) 

                    let res6 = await broker['broker'].call("megaind-rpi-v8.setOutputOpenDrain", { "stack": stackout, "channel": chout, "value": mv }, {} )
                    msg.payload = res6
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg) 
                    } else {
                        msg.payload = 'System disable'
                        setTimeout(() => { node.status({}) }, 500)
                        node.send(msg) 
                      }
                    } catch (e) {
                        node.status({ fill: 'red', shape: 'ring', text: 'error' })
                        node.error(e, msg)
                        setTimeout(() => { node.status({}) }, 500)
                    }
                })   
            } 

    //Begin of createPID4//
    function createPID4(node) {
        let broker = getBroker(node.broker)
        node.on('input', async (msg) => {
            try {
                let action = msg.action /*|| node.topic  */            /*msg.action comes from node-red graphical interface*/
                let options = msg.options || {}                        /*msg.options comes from node-red graphical interface*/
                let ident       = Number(node.ident)  
                        
                kp_id[ident]    = Number(msg.kp)
                ti_id[ident]    = Number(msg.ti)
                td_id[ident]    = Number(msg.td)
                daqpv[ident]    = Number(msg.pv)
                sp[ident]       = Number(msg.setpoint)          
                let enable      = Number(msg.enable)
                //let spdyn = node.spdyn
        
            if (enable === 1) { 
                //Chamada do PID.Plus//  
                 PID_param_set = 
                    {
                    "ti": ti_id[ident],
                    "td": td_id[ident],
                    "kp": kp_id[ident],
                    "pv": daqpv[ident],  
                    "setpoint": sp[ident],
                    "error": var_error[ident],
                    "integrative": var_integrative[ident],
                    "manipulatedVariable": var_mv[ident],
                    "time": var_time[ident]
                    }
                    
                    let PID_return = await broker['broker'].call("control-mesh-31.pidplus", PID_param_set, {}  )
                    //console.log(PID_param_set)
                    var_error[ident]        = PID_return.error[0]
                    var_integrative[ident]  = PID_return.integrative[0] 
                    var_time[ident]         = PID_return.time[0] 
                    var_mv[ident]           = PID_return.mv[0]
                    
                    node.status({ fill: 'blue', shape: 'dot', text: "CTRL Loop is: " +  var_mv[ident]}) 

                    let msg1 = {
                        payload: PID_param_set,
                
                    };
                    
                    msg.mv = var_mv[ident]   
                    setTimeout(() => { node.status({}) }, 500)
                    node.send([msg, msg1]);

                      

                } else {
                    msg.mv =  'Please enable the controls'
                    setTimeout(() => { node.status({}) }, 500)
                    node.send(msg)   
                }

            } catch (e) {
                node.status({ fill: 'red', shape: 'ring', text: 'error' })
                node.error(e, msg)
                setTimeout(() => { node.status({}) }, 500)
            }
        })   
        
    }  

    //beging createAction//
    function createAction(node) {
        let broker = getBroker(node.broker)
        let serviceName = getService(node.service)
        if (!broker['services'].hasOwnProperty(serviceName)) {
            broker['services'][serviceName] = {}
        }
        broker['services'][serviceName]['name'] = node.service.name;
        broker['services'][serviceName]['version'] = node.service.version;
        try {
            if (node.service.settingsType) {
                broker['services'][serviceName]['settings'] = RED.util.evaluateNodeProperty(node.service.settings, node.service.settingsType, node)
            } else {
                broker['services'][serviceName]['settings'] = JSON.parse(node.service.settings)
            }
        } catch (e) {
            broker['services'][serviceName]['settings'] = {}
        }

        if (!broker['services'][serviceName].hasOwnProperty('actions')) {
            broker['services'][serviceName]['actions'] = {}
        }
        broker['services'][serviceName]['actions'][node.topic] = (ctx) => {
            return new Promise((resolve, reject) => {
                node.status({ fill: 'blue', shape: 'dot', text: 'receiving request...' })
                setTimeout(() => { node.status({}) }, 500)
                let msg = {
                    action: node.topic,
                    payload: ctx.params,
                    _res: { resolve, reject },
                    emit: ctx.emit.bind(ctx),
                    broadcast: ctx.broadcast.bind(ctx),
                    call: ctx.call.bind(ctx)
                }
                node.send(msg)
            })
        }
    }

    //beging responseAction//
    function responseAction(node) {
        node.on('input', (msg) => {
            node.status({ fill: 'blue', shape: 'dot', text: 'sending response...' })
            setTimeout(() => { node.status({}) }, 500)
            if (msg._res !== undefined) {
                msg._res.resolve(msg.payload)
            } else {
                node.error('Request Action required', msg)
            }
        })
    }

};