asically a component that allows user to interact with the cluster
every object in kubernetes (pod, deployment, services, configmap) is represented by an API resource 

Each resource is assigned its own URL that is used to access the resource
if we have a number of deployment then we can get information of each individual deployment instance by exposing a URI which can be used to manipulate the resource 

resource vs object in kubernetes

resource can be though of as a blueprint, each resource has an endpoint associated with it and a yaml file that defines the schema of the resource

object is the instance of the resource that you create in your cluster, when we apply the resource's manifest file then we create its associated object in the etcd server

user write the pod spec and read the status of the pod
controller read the pod spec and write the status of the pod 

each object type has a associated controller object with it , for example a deployment type will have a deployment controller associated with it 