# TrajectoryRoutingDemo

The demo is shown in  2019 IEEE 38th Symposium on Reliable Distributed Systems (SRDS). The link of the demo paper is here: [A Testbed for Data Routing in Low-Power WSNs using DV-Hop Based Trajectory Encoding Algorithm](https://ieeexplore.ieee.org/document/9049569)
The current working demo is here: http://routing-demos.com:8080/

## System overview and UML model
As my GPU server is in the lab where I can't connect without using TCP socket, So I use the consumer and producer archetecture that using a server that connect to the user as well as the GPU server. It connect to user with nodeJS web server and connec to GPU server with the NodeJs TCP server. The UML model is shown below:
![systemModel](https://github.com/cxfcdcpu/TrajectoryRoutingDemo/blob/master/TrajectoryEncodingDemoOverview.PNG)
The UML class model look like follows:
![classModel](https://github.com/cxfcdcpu/TrajectoryRoutingDemo/blob/master/ClassModel.PNG)


## Usage 
The demo is in the address http://routing-demos.com:8080/
The detailed usage tutorial is shown in the pdf file:
[tutorial](https://github.com/cxfcdcpu/TrajectoryRoutingDemo/blob/master/document.pdf)

This github project only have the client part. It can be used as a GPU client that handel the computation load of encoding trajectory.
The front end is in another project which is a coorperate project with my undergraduate student Jimmy Lin
The NodeJS server is sololy writen by me.

In Linux with cuda installed.
compile: nvcc *.cu *.cpp -o client
To run: sh autorestart.sh

## Document
The documentation is generated with Doxygen. It is located in the [doc folder](https://github.com/cxfcdcpu/TrajectoryRoutingDemo/tree/master/DoxygenDoc)

## screen shot
Here is some screen shot of the demo:
![example](https://github.com/cxfcdcpu/TrajectoryRoutingDemo/blob/master/example.png)




