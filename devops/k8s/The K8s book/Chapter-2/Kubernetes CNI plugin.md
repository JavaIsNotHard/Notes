plugin that manages network interfaces
we define the networking model and the CNI implements that for us
the network model contains everything from the network stack to the endpoint or virtual interfaces to the actual physical interface that connects everything together to allow kubernetes networking


1. user initiates the creation of POD by sending a request to the API-SERVER, 
2. the API-SERVER contacts the kubelet running in the node that was picked by the scheduler
3. the kubelet delegates the responsibility of container creation to the CRI (container runtime interface), CRI also creates the network namespace for the container
4. CRI on creating the network namespace will call CNI (container network interface) to create virtual ethernet devices and establish routes

CNI does not handle traffic forwarding or load balancing, this job is the responsibility of the kube-proxy


responsible for allocating a subnet lease to each host out of a larger, preconfigured address space.

Platforms like Kubernetes assume that each container (pod) has a unique, routable IP inside the cluster. The advantage of this model is that it removes the port mapping complexities that come from sharing a single host IP.

in traditional container environment
```
docker run -p 8080:80 nginx 
docker run -p 8081:80 apache
```

- You can't run multiple containers that want to use the same port 
- If two applications both want port 80, you have to manually assign different host ports (8080, 8081, etc.) 
- You need to track which host port maps to which container

In Kubernetes, each pod gets its own unique IP address: 
- Pod A (nginx): 10.244.1.5 (always uses port 80 internally) 
- Pod B (apache): 10.244.1.6 (also uses port 80 - no conflict!) 
- Pod C (app): 10.244.2.10 (uses port 3000) 
- Pod D (database): 10.244.2.11 (uses port 5432)

this provides the following advantage:
1. No Port Conflicts
2. Makes routing with IP easier in cluster wide network



### How the Workflow Looks

To help you visualize where CNI fits in the process, here is the sequence of events when a Pod starts:

1. **Schedule:** The Kubernetes Scheduler assigns a Pod to a Node.
2. **Kubelet Triggers:** The Kubelet on that Node sees the new Pod and starts creating the container.
3. **Call to CNI:** The Kubelet looks at its configuration (usually in `/etc/cni/net.d/`) to see which CNI plugin is installed. It calls that plugin binary.
4. **CNI Execution:** The CNI plugin executes the `ADD` command: it assigns the IP, attaches the interface, and updates routing. 
5. **Pod Running:** Once CNI reports "Success," the Pod is marked as `Running`.

here are the roles of CNI in kubernetes cluster:
1. Assign IP address (IPAM): 
	- When a new Pod is created, it needs a unique IP address to communicate. 
	- The CNI plugin manages a pool of IP addresses
	- When the Kubelet (the agent on the node) requests a network for a new Pod, the CNI assigns an available IP from the pool to that Pod.
2. Network Connectivity:
	- Creating the network interfaces.
	- The CNI usually creates a virtual ethernet pair (veth pair). One end sits inside the Pod's network namespace, and the other end plugs into a bridge or interface on the host Node.
3. Pod-to-Pod Communication:
	- Every Pod must be able to communicate with every other Pod without using Network Address Translation (NAT)
	- Setting up routing or overlay networks.
	- The CNI plugin configures the routing tables on the node or creates an encapsulation tunnel (like VXLAN) so that a Pod on Node A can reach a Pod on Node B directly.
4. Enforcing Network Policies (Security)
5. Cleanup (Garbage Collection): 
	- Cleaning up network resources.
	- When a Pod is deleted, the Kubelet calls the CNI plugin again. The CNI must reclaim the IP address (putting it back in the pool) and delete the virtual network interfaces