Deployment is a Kubernetes resource that wraps ReplicaSet which is another type of resource and which finally wraps the Pod resource 

Deployment resource is mainly for -> rollbacks and rollouts
ReplicaSet -> self-healing

when you submit the yaml file to the API server then it creates a Pod spec, the kubelet monitors the API server for any updates that it is responsible for and if found then does the operations specified in the Pod spec such as creating pods and stuff

For most Kubernetes resources there is an associated controller with it, the same goes for Deployment resource as well. A Deployment controller observes and manages Deployments 

A resource is an object that represents a desired state of something in the cluster and a controller is something that watches the resource and compares the current state of the resource with the desired state and performs reconciliation to get to the desired state

As the API server parses the YAML file, it creates an internal object such as Go structs and stores that struct in the etcd state manager. So basically our Deployment object represents just the desired state of the cluster and resides in the API server's etcd storage whereas the Deployment controller also resides control plane but as a resource controller separate from the actual resource

