there are two layers:
1. the frontend 
2. the backend

the frontend layer is responsible for defining the IP address, DNS name and port
these values are guaranteed by the kubernetes to never change

the backend is a label selector that sends traffic to healthy pods with matching labels

we have to send traffic to a separate service instead of directly sending the traffic to the pod is because of the mortal nature of the pods in kubernetes since pods are stateless and can be rollbacked rolledout crashed and many more

Services are intelligent enough to keep a list of healthy pods with matching labesl 

how does kubernetes do this?
using EndpointSlice 
what are endpointslices?
they are data structures we find in go like slices which keeps track of healthy pods in the cluster 


types of services
1. ClusterIP -> used for internal communication of the cluster and cannot be accessed outside the internal network. ClusterIP is a virtual IP that is allocated to a service 
2. NodePort -> nodeport is built on top of clusterIP and allows external clients to connect via an exposed port on the node 
3. LoadBalancer

cluster IP -> 
we create an app called something and to access that service we also need a service that allows us to access externally or internally
we create a service called something as well for the something app then kubernetes creates a ClusterIP service with the same something name 
this service assigns an internal IP address and creates a DNS record in the cluster's internal DNS server 
since the DNS is internal ClusterIP are aren't routable 
kubernetes then assigns it its IP address and 

NodePort is built on top of the functionality built by ClusterIP such as internal IP address as well as DNS record as the hostname 
what does NodePort do?
it exposes Port on each cluster node, whenever request comes in for this port number then it routes the request to the Service which then routes the request to the appropriate port based on the mapping defined in the YAML file

step1: external client hits a node in the cluster 
step2: node forwarding the request to the ClusterIP of the service 
step3: the service picks a node based on the healthy list of pods in the endpointslice 
step4: the service sends the request to the appropriate pod



what is cluster DNS service?


