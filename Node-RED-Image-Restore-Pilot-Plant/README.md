# Node-RED image restoration

Below are the services currently running on moleculer REPL, they are required to the proper function of the control loops.
<p align="center">
 <img src="src/moleculer_services.png" />
</p>

## From Docker-Hub:

Once Node-Red applications were conteinerized you can install from the public directory under the command:
      docker pull eviana/pilot-plant-node-red-image:latest

And run the container via Docker Hub at rasp prompt:
      docker run --name node-red-iotgasi -p 1880:1880 eviana/pilot-plant-node-red-image:latest

## Notes: 
Any further configuration can be easily done thru Portainer at 192.168.1.108:9000 [admin/admin]
The image above contains all functionalities already working, anyhow if you need to install any additional blocks, please see below commands:


The containerized Node-Red image for Pilot Plant 4.0 control was stored in Docker Hub at the address:
eviana/pilot-plant-node-red-image

The following steps must be taken: 

1-Download the image thru the following command:
     docker pull eviana/pilot-plant-node-red-image:latest (don´t you use sudo command)

2-Run docker command and build the container:
     docker run --name node-red-iotgasi -p -1880 eviana/pilot-plant-node-red-image:latest

3-Use portainer to easily manage the container named "node-red-iotgasi"


Please test and provide feedback to: eduardo.viana@unesp.br

  
