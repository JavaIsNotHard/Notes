plugin that manages network interfaces
we define the networking model and the CNI implements that for us
the network model contains everything from the network stack to the endpoint or virtual interfaces to the actual physical interface that connects everything together to allow kubernetes networking


1. user initiates the creation of POD by sending a request to the API-SERVER, 
2. the API-SERVER contacts the kubelet running in the node that was picked by the scheduler
3. the kubelet delegates the responsibility of container creation to the CRI (container runtime interface), CRI also creates the network namespace for the container
4. CRI on creating the network namespace will call CNI (container network interface) to create virtual ethernet devices and establish routes

CNI does not handle traffic forwarding or load balancing, this job is the responsibility of the kube-proxy
