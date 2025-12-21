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