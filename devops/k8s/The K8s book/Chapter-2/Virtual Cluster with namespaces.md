namespaces are used mainly for internal multi tenant application and are not so common to divide a cluster among external tenants, instead we can allow external tenants to run them on their own cluster and their own hardware, this way we can isolate one tenant with another. this is called hard isolation between tenants

namespace provides soft isolation such as apply different policies for different namespaces such as dev, prod, test and more. internal multi tenant application also allows organization to divide the cluster into categories such as finance, corporate-ops and more 

since namespace provides soft isolation, a compromised workload in one namespace cannot prevent another workload from another namespace to be compromised 


Kubernetes provides us with a predefined set of namespaces such as 
- default  -> all the objects that we create are placed on this namespace
- kube-node-lease  -> hand
- kube-public 
- kube-system


command to set the namespace for all the kubectl commands to make sure we don't have to specify --namespace for every command
`kubectl config set-context --current --namespace <namespace name>` 