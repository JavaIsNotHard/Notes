
pods that are directly managed by the kubelet instead of delegating those responsibility to the api server and kube-scheduler

the pod object is still visible from the api server even though it may not manage the pod

automatic restarts are handled by kubelet when the pod crashes, when the YAML manifest file is deleted then the pod is removed from the node

most of the control plane components are ran as static pods

services that must run on specific nodes and shouldn't be moved or rescheduled

