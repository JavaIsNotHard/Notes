kubectl get pods -n kube-system

communication between pods happens through the pod's service
to send request from one pod to another, two things are needed
1. know the name of the communicating app
2. way to convert the name into an IP address 

![[Screenshot 2025-06-18 at 11.50.29 AM.png]]

service registry maintains a list of apps and maps their name with their IP address

kubernetes uses the service registry as a built-in cluster DNS and it runs on the control plane
the cluster DNS runs as a Deployment and has its own Service, the deployment is called coredns or kube-dns and the service is called kube-dns

![[Screenshot 2025-06-18 at 11.56.09 AM.png]]

service registration

The registration process is automatic because the cluster DNS is a Kubernetes-native application that watches the API server for new Services. Whenever it sees a new one, it automatically registers its name and IP.

![[Screenshot 2025-06-18 at 12.02.10 PM.png]]

service discovery
Kubernetes configures every container to use the cluster DNS for service discovery. It does this by automatically configuring every container’s /etc/resolv.conf file with the IP address of the cluster DNS Service.

service discovery and namespace
fully qualified domain names has a format of the type <object-name>.<namespace>.svc.cluster.local