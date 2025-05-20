Kubernetes exposes a REST API over HTTPS for external as well as internal communication
all the request that is send to Kubernetes goes through the API server and all request that it receives are authenticated and authorized 

Deploying an app in Kubernetes includes the following steps:
1. Describing the application in a config file with .yaml extension
2. We then apply the yaml file to the API server using the `kubectl apply -f <file name>.yaml` command, this command sends the .yaml file to the API server
3. the API server then authenticated and authorizes the client that sent the request, the client sends a POST request to the API server's endpoint with Bearer tokens alongside the request
4. The state of the application defined according to the .yaml file will then be stored in a [[cluster store]] typically etcd which is a highly available distributed key value store for used by Kubernetes 
5. Then the scheduling algorithm running in the control plane will schedule our application, the kubelet on those node will then pull the container from container registries 

