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

