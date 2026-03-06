
the control component watches the health of all the active nodes

if the node is not healthy or has not started for a certain period of time then the pod is evicted from the cluster

if pod is part of a ReplicaSet and the pod has a minimum requirement of 1 pod per node then when a node is not available for a certain duration, the kube-scheduler will run the pod in a separate running node automatically

the time it waits for the pod to come back online is called as pod-eviction timeout 

the kube-controller-manager is set with a pod-eviction timeout which is the amount of time the controller manager waits for the pod to come back healthy, if not then then the pod is considered dead


this means even if the node is down and the pod is evicted, then the pod will be rescheduled to another node after the eviction timeout, if the business logic allows the application to be down for the eviction timeout and there is another node that is running the pod then we can perform OS upgrades and down it for server maintenance

but if that is not allowed then what do we do??

we can drain the node of all the workloads, such that the workloads are moved to another server
```
kubectl drain node-1
```

this gracefully terminates all the pod in the node and recreates it in another node, also the node is marked as not schedulable until we specifically remove this restriction

now we can reboot the node and uncordon it such that it can be rescheduled using this command
```
kubectl uncordon node-1
```

there is another command
```
kubetl cordon node-1
```

this doesn't drain the node with all its pods but rather marks the node as unschedulable until it is `uncordon` manually

