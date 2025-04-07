why kubernetes ?
- abstracting away the infrastructure from the developers 
- builtin support by all cloud providers hence better cloud native support for services

- it frees developers from the need to implement infrastructure-related mechanisms in their application. it provides the following features
	- auto-scaling
	- service discovery 
	- leader election
	- self-healing

- kubernetes architecture contains 2 important components
	- control plane : contains computing units commonly referred to as master nodes
		- API service 
			- provides mechanisms for the end user to communicate and interact with kubernetes master plan
		- controller manager
			- performs cluster level functions such as replication, keeping track of working nodes, handling node failures and more
		- etcd or other coordination service
			- distributed configuration management coordination
		- scheduler 
			- schedules new pods to worker nodes
	- workload plane : contains worker nodes whose job is to only host the actual container. It contains the application that we are trying to deploy and run
		- kubelet 
			- talks to the API server and manages containers on each node
		- kube-proxy
			- handles network related stuff, acts as load balancer, filters out traffic and allows rate limiting and much more
		- container runtime
			- docker container


main job of kubernetes is to manage container, so we do need a working container image for kuberentes

- minikube : helps to setup a local kuberetes cluster without needing cloud services
- kubectl : interact with the kubernete's control plane's API server to manage the cluster and pods and containers running inside it

![[Screenshot 2025-02-24 at 3.10.41 PM.png|600]]

### starting a cluster in minikube
```
minikube start
```

## getting cluster information
```
kubectl cluster-info
```

### getting running nodes 
```
kubectl get nodes
```
nodes in kubernetes are physical computers that run the kubernetes server

### deploying a container image from docker hub repo
do deploy your container image in kubernetes, you first need to push your local container image to docker hub 
```
kubectl run <name of pod> --image=<image_name> --port=8080
```


## Pods in kubernetes
- containers are not standalone objects in kubernetes, pods are
- pods are different from containers
- containers that are closely coupled are placed together into a single pod 
- containers in the same pod share the same namespace, all the containers running in the same pod will appear to be running in the same logical machine 

![[Screenshot 2025-02-24 at 3.16.19 PM.png|600]]

### get all active pods 
```
kubectl get pods
```
- if we immediately run this command after creating the pod then we get its status as "PENDING" because the pod needs to pull the container image from docker hub and do some other stuff before getting ready

## behind the scenes 
![[Screenshot 2025-02-24 at 3.20.33 PM.png|600]]
- first we push the docker image to a registry (mainly docker hub) because we want the image to be accessible to the worker nodes inside the cluster as well 
- we then run the `kubectl run` command with the image name


### creating services in kubernetes
- `kubectl expose rc <pod_name> --type=<type> --port <port_number>`
- the following command creates a service object which is used to interact with the pod internal to the cluster
- a service object of type LoadBalancer is used to generate a uniform static IP address that external services use to communicate with the pods since pods are assigned private IP address of the worker node they are running on

- LoadBalancer services does not provide the load balancing function itself
- if the cluster is deployed in a cloud environment that supports load balancing, then the cloud will itself provide a separate load balancing function and assigns an IP address for the load balancer
- the load balancer then forwards request to the pods

- minikube cluster do not have the provision of load balancing
- the command `minikube service <service_name> --url` will return a url where your application is exposed 
- the IP address returned is the IP address of the VM that minikube starts and the port number is something called a NodePort
- it is the port number of the worker node that forwards connections to the cluster's services.


## logical view of kubernetes working
- replicationController
- service
- pod
- when we ran the `kubectl run` command we created a replicationController which was responsible for creating the pod (which pull images from docker hub)
- this pod or the worker node is not accessible directly from external hosts because they do not have any external IP address and can only communicate within the pod or within the worker node
- so we also created a external service which we can interact with which would then forward our request to the worker node and to the pod running our container

- a replicationController is a kubernetes object
- the job of a ReplicationController is to make sure that the specifies number of replica are running at an instance of time. 
- Suppose we specified 3 replicas in the manifest of ReplicationController pods then the scheduler sure that at a time all 3 of them are running. if a pod is down, then the scheduler creates a new pod and if more than 3 pods are up then they are removed from the worker node

- the job of a LoadBalancer service in kubernetes is to solve the problem of changing IP address of pods when old one dies and a new one is created and added to the worker node
- it exposes multiple pod replicas using a single constant IP address and communicates with clients outside the kubernetes cluster


### what is a kubernetes object?
- represents persistent entity which helps us maintain the state of our cluster
- here state refers to the configurations of the application that you are trying to deploy or run


## creating a kubernetes object through a manifest file

- `kubectl create -f <file_name>.yaml`
- A kubernetes manifest file contains 3 main components
	- metadata
	- spec
	- status

### Viewing logs 
- we can view all the logs that the container produces in its standard output and standard error by using the command 
	- `kubectl logs <pod_name>`
	- OR if we have more than one container in a pod then
	- `kubectl logs <pod_name> -c <container_name>`

### port forwarding to reach application without defining a service

- `kubectl port-forward <pod_name> target_port:source_port`
- this way we do not have to create a service for sending request to our pod 


### Labels in kubernetes
- adding the `labels:` option in the manifest file 
- or using the command `kubectl label pods|rc|deploy|node... <name_of_object> <list of label>`, something like `kubectl label po new-pod env=prod`

- `kubectl get po --list-labels` will list all the associated labels 
- `kubectl get po -L <label1> <label2>` will list all labels as its own column


### Label selector
- we use the `-l` flag to select pods from a cluster based on their label
- `kubectl get pods -l 'env=prod'` will select all the pods with label `env=prod`
-