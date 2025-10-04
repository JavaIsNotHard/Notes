An **API object** in Kubernetes is any entity you create, update, or delete via the **Kubernetes API**
These objects describe the **desired state** of your cluster (what you want).
The controllers and kubelet work to make the **actual state** match the desired state.

API object is defined using a YAML file 

```
apiVersion: v1          # API group + version
kind: Pod               # Object kind (resource type)
metadata:               # Name, namespace, labels
  name: my-pod
  namespace: default
spec:                   # Desired state (what you want)
  containers:
    - name: nginx
      image: nginx:1.25
status:                 # Actual state (set by Kubernetes)
  phase: Running

```


**An API object = a concrete instance of a Kubernetes resource, stored in etcd and managed via the Kubernetes API.**

