Container network model 
specification of how network should be implemented in containers 
libnetwork is the actual implementation of the CNM specification 
Drivers -> manages the network, this includes:
- bridge
-  host 
- overlay 
- IPvLAN 
- macvlan 


The container network model contains the following components 
- sandbox -> 
	- the actual network stack of the container
	- each container has independent network stack 
	- it includes IP tables, DNS configs and other network related stuffs 
-  endpoint:
	- connection point between the sandbox and the network 
	- can be thought of as a bridge between the container network stack to the docker network 
	- can also be thought of as a network adapter that can only connect to a single network 
- network:
	- virtual switches or routers
	- types of network are the drivers mentioned above 

each endpoint can be connected to a single network 
endpoints that are connected to the same network can communicate with each other 


`docker0` interface which is a bridge interface between the host machine's network stack and the docker network stack 
this means a container sends data into the network through the docker0 bridge interface to the host machine and then to the internet 
any new container that needs a network is assigned by docker0 interface if no other network type i used i.e if the docker0 interface has an subnet of 172.16.0.0/16 then it assigns IP address of that ranged subnet 

Each container has its own network stack and a endpoint
the network stack 


A host has a network interface like eth0 in mac wlan0 in linux for wireless NIC which represents a bridge between the OS and the NIC itself

This network interface is used to communicate with computers outside of the local network or inside the network itself

Similarly for a container to access internet and send packets through the internet it needs a network interface, Docker creates a default docker0 bridge network interface which communicates with the containers running on the default bridge network, allowing them to communicate with each other and with the host machine.


Sandbox is the network namespace associated with a docker container
it isolates the container's network stack from the host and other containers 
the sandbox provides the container with their own IP, interface, routing table, DNS and more 
includes a loopback interface `lo` for internal communication 

Network provides the communication scope of the containers
it tells if and which containers can communicate with each other 
For example if the container is using a bridge network then containers in the same bridge network can communicate with each other 

Endpoints are a virtual connection between the container's sandbox and the docker network 
when an endpoint is created then docker sets up a network virtual network interface such as veth to enable network communication outside the container 

linux bridge is a virtual switch that allows multiple network interfaces to communicate with each other that are connected to the bridge 
docker0 is a linux bridge, 
for each container, docker creates a veth pair, one end of the veth is placed inside the container(eth0) while the other end is attached to docker0
all container network request are sent via the veth pair to the docker0 bridge 


The docker bridge network maps to the linux host machine's docker0 interface which is implemented using linux bridge technology 
containers are connected to the bridge network by default which in turn maps to the docker0 bridge in the host's kernel 

the veth pair has an interface in both sides i.e in the container side with a network interface such as eth0 and the host's kernel side as vethXXXX
one is connected to docker network and the other is connected to the associated bridge in the kernel

![[Screenshot 2025-01-09 at 4.26.19 PM.png|500]]



What I learned from [Ivan Velichko's article][https://labs.iximiuz.com/tutorials/container-networking-from-scratch]
- containers have their own network namespace 



How does service discovery work in user defined network in docker?
- the `/etc/resolv.conf` file tells where the DNS is available 