ingress refers to the act of entering

ingress means the traffic that enters the cluster and egress means the traffic that exits the cluster 

ingress in kubernetes is a native resource like pods, deployments etc
the ingress controller does the routing by examining the routing rules from ingress object stored in etcd

basically ingress is used to define routing rules for all the traffic entering the cluster

ingress is a resource rather than a service like a Type LoadBalancer which exposes a external IP and just forwards the request to the NodePort of ClusterIP type

ClusterIP -> assigns virtual IP

virtual IP -> IP that doesn't belong to the one single pod instead it is a cluster-wide IP that represents a service

ClusterIP gets its IP range from the interaction of API server and kube-proxy
- when the API server is first started then it starts the server with flag `--service-cluster-ip-range` which defines the IP range 
- when we create a `Service` of type `ClusterIP` then API server automatically assigns a free IP based on the service CIDR 
- the kube-proxy runs in every node and when it sees changes in the `Service`, it sets up iptable rules so that any traffic to the specific IP is redirected to one of the backend pods




NodePort : it exposes a port on a specific node which allows external traffic in a specific IP address and a specific node



before Ingress, a custom Nginx or HAProxy kubernetes deployment would be exposed as LoadBalancer service to route external traffic to internal cluster service
the routing rules are defined in a separate ConfigMap object 
whenever there is changes in the dns or a new route entry is defined it gets updated in the configmap and pod configs are reloaded

ingress has the routing rules maintained as a native kubernetes ingress object instead of configmap

and instead of Nginx and HAproxy, we have the ingress controller which fetches the routes dynamically

two main components in kubernetes ingress:
1. kubernetes ingress resource
2. kubernetes ingress controller

there is no default implementation of kubernetes ingress controller native to kubernetes
we need a controller for the ingress rules to work, so we need to depend on open source ingress controller implementation

the yaml file defines all the routing rules for the cluster, these rules are stored in the kubernetes ingress API

the kubernetes controller talks to the kubenetes api server if there is a correspoding rule defined in the server





