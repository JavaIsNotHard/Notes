exposes service inside a cluster to all the nodes inside the same network,

NodePort is a type of ClusterIP that is also reachable at the IP of the  node as well the ClusterIP on the service network 

the type NodePort creates two netfilter rules, one at the node level at the eth0 interface related to the node IP and another rule related to cluster IP to pod IP translation

the first rule says the following:
- when traffic arrives at <Node_IP>:<Node_Port> then forward the request to a ClusterIP
- for this, kube-proxy exposes a random port number at the eth0 interface and then writes a rule associated to this port number
- when netfilter intercepts request at our specified addr then it performs a DNAT to change the destination IP to cluster IP
the second rule says the following
- when traffic arrives at Cluster IP then forward the request to one of the healthy pod

here we have another problem, node port only exposes node port at the node's IP address which in most cases is a private IP assigned by the ISP's router

external clients need a way to access the services hosted at a private IP address, which is done by [[Load Balancer]] service type