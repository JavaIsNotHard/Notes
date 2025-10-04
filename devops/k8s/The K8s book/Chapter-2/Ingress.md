Using LoadBalancer Resource type in Kubernetes has a disadvantage that for each new service it needs a separate LoadBalancer resource which doesn't scale very well 

so instead what we can have is something like an API gateway that forwards request to the underlying downstream service without needing to increment the server with increase in the service 

for that we use Ingress server. Ingress has two main constructs which includes:
1. the controller 
2. the resource

the resource is used to defined the routing rules such as path based routing and host based routing whereas the controller is used to implement such routing rules in the server itself. so basically the resources is stored as a YAML file in the source of truth or the etcd server

the resource or the config file for the ingress server is written us to help us define the routing rules but the controllers are implement but some third party applications such as ingress-nginx-controller or traefik and more

ingress operates on layer 7 of the OSI layer which is the application layer and helps us filter and route traffic based on application level protocols such as HTTP/HTTPS, DNS and more

the Ingress controller needs a load balacner which is placed before the ingress controller. the load balancer works like a reverse proxy which accepts all the user request and exposes the IP for the user to communicate to but all the routing functionality is done by the controller so all the request that the load balancer receives are forwarded directly to the ingress controller

