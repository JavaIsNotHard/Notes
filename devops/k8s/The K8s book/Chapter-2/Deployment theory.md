Deployment is a Kubernetes resource that wraps ReplicaSet which is another type of resource and which finally wraps the Pod resource 

Deployment resource is mainly for -> rollbacks and rollouts
ReplicaSet -> self-healing

when you submit the yaml file to the API server then it creates a Pod spec, the kubelet monitors the API server for any updates that it is responsible for and if found then does the operations specified in the Pod spec such as creating pods and stuff

For most Kubernetes resources there is an associated controller with it, the same goes for Deployment resource as well. A Deployment controller observes and manages Deployments 

A resource is an object that represents a desired state of something in the cluster and a controller is something that watches the resource and compares the current state of the resource with the desired state and performs reconciliation to get to the desired state

As the API server parses the YAML file, it creates an internal object such as Go structs and stores that struct in the etcd state manager. So basically our Deployment object represents just the desired state of the cluster and resides in the API server's etcd storage whereas the Deployment controller also resides control plane but as a resource controller separate from the actual resource



Deployment autoscalers include:
1. Horizontal Pod Autoscaler -> adds and removes pods
2. Vertical Pod Autoscaler -> increases and decreases the resources for the pod such as memory and CPU
3. Cluster autoscaler -> adds and removes nodes from the cluster

but we can also manually scale our deployments


whenever the horizontal pod autoscaler cannot find a node that matches the required resources then the cluster autoscaler kicks in to add new nodes to the cluster that matches our requirements. Pods that cannot find the required node are created in Pending state

The ReplicaSet controller makes sure that correct number of pods replicas are present in our node 


Rolling updates and rollbacks in Deployments 

zero-time rolling updates can be achieved if the application is designed with the following needs:
1. loosely coupled via API
2. backward and forward compatibility

backward compatibility -> new version of the code works with older clients
forward compatibility -> old version of the code works with newer clients

here is what happens during a rolling update:
- suppose there needs to be a security fix in the application code and the configuration has to be changed for that
- the YAML file is edited to make sure to fix the problem and send to the API server 
- the API server updates the Deployments with a new desired state requesting the same number of pods but all running newer versions of the code 
- once the API server changes the Deployment object, the desired state no longer matches the current state which means reconciliation needs to be done
- for this the deployment controller creates a new ReplicaSet object inside it that will hold our new version of the pod
- the update from older version to the newer version is done incrementally and smooth by incrementing newer pod and decrementing older pod at the same time if possible

to support rollbacks, the previous version or the old version of replicaset's configuration is not removed entirely from the deployment to make sure that we can rollback easily i.e create pods based on the configuration in the previous version