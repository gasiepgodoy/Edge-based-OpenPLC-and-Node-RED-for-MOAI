from setuptools import setup, find_packages

from os import path

this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

setup(
    name='moleculer-client',
    version='0.1.6',
    description='Simple Client in python to communicate with MoleculerJs Microservices using NATS',
    long_description_content_type="text/markdown",
    long_description=long_description,
    author='Caio Filus Felisbino',
    author_email='caio.filus@gmail.com',
    url='https://github.com/CaioFilus/moleculer-client',
    license='MIT',
    packages=['moleculer_client'],
    install_requires=[
        'nats-python==0.7.0',
    ],
    include_package_data=True,
    keywords=['python', 'microservices', 'NATs'],
)
