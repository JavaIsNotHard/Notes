
taint and tolerant controls which pods are allowed to be scheduled on which nodes

taint : applied to nodes, don't schedule a pod unless it has tolerant for this taint
tolerant : applied to pod, allows pods to run on a tainted node

the format of a taint is as follows:

```
kubectl taint nodes <node_name> <key>=<value>:<Effect>
```

what are effects??
defines what happens to pod that don't have a matching tolerant 

here key and value can be anything whereas effects can have the following possible values:
1. NoSchedule : New pods without the tolerant will not be scheduled into this pod, existing pod will keep running
2. PreferNoSchedule : Tries to avoid placing new pods into this node but does not guarantees this
3. NoExecute : New pods without tolerant are blocked and existing pods without tolerant are also evicted immediately, we can also define a tolerationSeconds option which defines how much do we wait 


Control-plane nodes are tainted with:
```
node-role.kubernetes.io/control-plane:NoSchedule
```
this prevents pods to be scheduled on the control node


format of a toleration is as follows:
```
apiVersion: v1
kind: Pod
metadata:
  name: nginx
  labels:
    type: something
spec:
  containers:
  - image: nginx
    name: nginx
  tolerations:
  - key: "key"
    value: "something"
    operator: "Equal"
    effect: "NoSchedule"
```


to untaint a node we use the command:
```
kubectl taint nodes node1 dedicated=gpu:NoSchedule-
```

here the `-` is used to untaint a taint in a node


command to list all taints applied to a node

```
kubectl get nodes -o json | jq '.items[] | {name: .metadata.name, taints: .spec.taints}'
```

command to list all tolerants on pods

```
kubectl get pods -A -o json | jq '.items[] | {name: .metadata.name, namespace: .metadata.namespace, tolerations: .spec.tolerations}'
```

