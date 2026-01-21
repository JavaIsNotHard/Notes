### Pods 
A pod consists of one or more containers that are collocated on the same host, and are configured to share a network stack and other resources such as volumes

same network stack -> it means that all the containers in a pod can reach each other on localhost.  If I have a container running nginx and listening on port 80 and another container running scrapyd the second container can connect to the first as http://localhost:80

![[Pasted image 20250915214420.png | 400]]

eth0 => physical interface 
docker0 => bridge that connects the host to the container
veth0 => host side virtual link, the container also container a veth pair that relays packets from container to veth0 to docker0 to eth0 to the internet


![[Pasted image 20250925145836.png | 400]]

here we have two containers inside a single pod
there are two veth pair veth0 and veth1 in each of the containers
each veth pair is connected to a bridge type called docker0
but this configuration still doesn't provide the shared network stack feature because the container still requires a different IP to communicate with one other

![[Pasted image 20250925150315.png | 400]]

for the shared network stack we use the above configuration where both container are in the same veth0 pair which means that they can communicate with one other using localhost

![[Pasted image 20250925153829.png | 400]]

the above is a scenario when we have two communicating hosts connected with each other using a router/gateway between them.
the router has the address 10.100.0.1
the first host has the address 10.100.0.2
the second host has the address 10.100.0.3
the application running on each host can communicate with one other using the eth0 interface in each side through the routing rules defined in each host as well as in the router
But in kubernetes, communication doesn't happen between hosts, between rather between pods and pods have their private address space, these pods are in a different network, the bridge network which connects the containers inside the pod

![[Pasted image 20250925153655.png | 400]]

the above is the entire networking stack that helps in communication between two pods running on two different nodes
first kubernetes network plugin must assign an overall address space for the bridges on each node then assign each bridge in the cluster an IP address from the address space
the network plugin also adds routing rule in the router telling it how packets destined for each bridge should be routed, i.e. which node’s eth0 the bridge can be reached through


### Services 
Pod networking in a cluster is neat stuff, but by itself it is insufficient to enable the creation of durable systems. That’s because pods in kubernetes are ephemeral. You can use a pod IP address as an endpoint but there is no guarantee that the address won’t change the next time the pod is recreated, which might happen for any number of reasons.

A service is a type of kubernetes resource that causes a proxy to be configured to forward requests to a set of pods

ClusterIP is the default and it means “the service will be assigned an IP address reachable from any pod in the cluster.”

```
$ kubectl describe services service-test  
Name: service-test  
Namespace: default  
Labels: <none>  
Selector: app=service_test_pod  
Type: ClusterIP  
IP: 10.3.241.152  
Port: http 80/TCP  
Endpoints: 10.0.1.2:8080,10.0.2.2:8080  
Session Affinity: None  
Events: <none>
```







