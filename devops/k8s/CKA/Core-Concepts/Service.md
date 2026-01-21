a kubernetes object that persists IP address for a pod in the cluster

how??

using iptables, ebpf, ipvs and more

the kube-proxy watches the api-server for any new services that are created
since kube-proxy runs on each worker node it will change the kernel level net filter to redirect traffic that arrives at the service IP
service are not actual process that runs on the worker node but rather they are non-existent, they don't have a persisting IP, network interface or anything
when a packet arrives at

Is the service proxy aware of healthy server pods that can handle requests? As mentioned above kube-proxy listens to the master api server for changes in the cluster, which includes changes to services and endpoints. As it receives updates it uses iptables to keep the netfilter rules in sync


how does kube-proxy handle unhealthy endpoints or pods?
the kubelet performs healthchecks against those endpoints, when unhealthy endpoints are found, kubelet notifies the kube-rpoxy via the api-server and netfilter rules are edited to remove this unhealthy endpoint from the rule list


we have 3 main interface in a node
1. veth: connects the pod to the node
2. cni0: allows pods on the same node to communciate with each other
3. flannel.1: performs the encapsulation for node to node communication



if the NAT translates the cluster IP to one of the healthy pod's IP then what is the use of service here?
each node's iptable will be configured such that when the dest IP is the clusterIP then it transforms it into one of the healthy pod's IP


### 1. Inside the Pod (The Origin)
The Pod has no idea that the "Service" is a virtual concept. It treats the ClusterIP like a real physical server.
- **The Packet:** The application creates a standard IP packet.
- **Source Address:** Pod A's IP (e.g., `10.244.1.5`).
- **Destination Address:** The Service ClusterIP (e.g., `10.96.0.100`).
- **Encapsulation?** **No.** At this stage, it is a normal, naked IP packet. It travels through the `veth` pair to the Node

### 2. At the Node (The Translation)
Once the packet hits the Node's root network namespace, `iptables` or `IPVS` (managed by `kube-proxy`) intercepts it **immediately**.
- **The Action:** DNAT (Destination Network Address Translation).
- **The Change:** The kernel looks at its load-balancing rules and picks one of the healthy backend Pods. It **overwrites** the destination address.
- **The New Packet:**
    - **Source:** `10.244.1.5` (Pod A)
    - **Destination:** `10.244.2.10` (**Real Pod B IP**)
- **Encapsulation?** **Still No.** It is still a standard IP packet, but the "target" has been switched from the virtual Service to a real Pod.


### 3. Leaving the Node (The Encapsulation)
Now the Node’s routing table looks at the new destination (`10.244.2.10`). It realizes this Pod lives on **Node 2**. This is the moment where encapsulation happens.
**Why do we still need it?** Because even though we now have a "Real Pod IP," the physical network (your Cloud VPC or Office Router) still doesn't know where `10.244.2.10` is. It only knows Node IPs.
- **The Component:** The **VTEP** (`flannel.1` or `vxlan.calico`) takes the translated packet.
- **The Action:** It wraps the entire packet inside a **UDP Envelope**.
- **The Final "On-the-Wire" Packet:**
    - **Outer Source:** `192.168.1.10` (Physical IP of Node 1)
    - **Outer Destination:** `192.168.1.11` (Physical IP of Node 2)
    - **The Payload:** The translated packet (Pod A IP $\rightarrow$ Pod B IP).


## EndPoints

endpoints are the pods where the traffic are routed to by the service
it is an object that contains a list of IP and ports 
there can be multiple endpoints for a specific service, which enables service to load balance between them

based on the matchselector defined in our service.yml file, it creates endpointslices


how does service or controllers keep track of all healthy endpoint slices?

- api server monitors for any. new serivce types
- kubelet sends pod metrics to api server which is read by different controlers and updates the pod status which is read by the endpoint controler
- endpoint/endpointslice controller are responsible for monitoring tasks

The **EndpointSlice controller**:
- Watches Pods + Services
- Matches Service selectors to Pods
- **Includes ONLY Ready Pods** in Endpoints

kube-proxy watches the endpoint object for new changes and updates its local worker node accrodingly



```
10.42.2.0/24 dev cni0 proto kernel scope link src 10.42.2.1
```

this rule says that the CIDR addr range 10.42.2.0/24 is local pod addr range and any packet designated to this cidr range will be forwarded to cni0 interface i.e all the packets will be forwarded through the bridge cni0

```
10.42.0.0/24 via 10.42.0.0 dev flannel.1 onlink
```

this rule says that all the packets of the destination cidr range 10.42.0.0/24 will be forwarded through the flannel.1 interface


### Kube-proxy

the kube-proxy actively monitors the API server for endpoint changes and sets new netfilter rules based on those changes. for example, if we delete all the pod endpoint associated with a service then the following rule is applied

`-A KUBE-SERVICES -d 10.43.131.159/32 -p tcp -m comment --comment "default/service-test has no endpoints" -m tcp --dport 80 -j REJECT --reject-with icmp-port-unreachable`

this rule tells that any request for this cluster IP returns ICMP "port unreachable" error because there are no endpoints associated with this sevice


### Ingress : traffic from external clients

how to allow external clients to access services deployment in a k8s cluster??

kubernetes services operate in layer 3 (routing layer) i.e netfilter apply changes to IP datagram. routing inside the cluster is performed using the information contained in the packet related to IP

when a packet has a destination of a ClusterIP, then netfilter intercepts the packet and performs DNAT to change the destination IP from cluster IP to address of one of the running pods

Connections and request are layer 4 and layer 7 respectively
for external clients to connect to a pod that is backed by a service, the client needs to know the cluster IP and port of the service
but the netfliter rules for translating cluster IP to pod IP is not set on client's interface which brings a new problem 

why rely on external load balancer instead of kubernetes instead to handle external traffic??

1. node ephemerality : nodes are ephmeral, they can be migrated to new virtua machines, and cluster can scale up and down
2. the next hop problem: traditional routers operating at layer 3 require a stable "next hop" node to forward the packet, if kubernetes managed the external routes then it would have to constantly update the routes every time a node fails to prevent the route from breaking

we run our web application at port 80 of a pod's IP address
an gateway router that is employed between the external client and the cluster has a route only to the nodes of the cluster, which means that the gateway router do not know how to forward packets to the pod which also means the gateway router cannot work with cluster IP because the netfilter rules are applied to the eth0 interface of the node but gateway router does not know about the clusterIP of the service

suppose an external client tries to reach a server at port 80 through the gateway server as follows
dst addr: 10.100.0.2:80
the gateway forwards the packet to the destination node 10.100.0.2 and port 80
but since our web application is serving request at pod level, the packet is dropped because there is no service listening on port 80 at addr 10.100.0.2

if the gateway router somehow knew the clusterIP then the eth0 interface at the node 10.100.0.2 would translate the clusterIP to one of the stable pod IP and the packet would successfully reach its destination


here is where [[NodePort]] comes it play
