replication controller spans across multiple nodes in the cluster
helps with load balancing and scaling

replica controller (old and being replaced with replica sets )


ReplicaControler vs ReplicaSet
- ReplicaSet uses LabelSelector to choose which pods that ReplicaSet will manage

why does the ReplicaSet definition require the definition of the Pod template even if we already have define which pod labels to match??

because if one of the pod inside the replicaset where to fail then replicaset needs to know how to start a new pod of the same type

how to scale the ReplicaSet??
kubectl replace -f replicaset-definition.yml // after modifying the spec.replicas value
kubectl scale --replicas=<no of replicas> -f replicationset-definition.yml //
kubectl scale --replicas=<no of replicas> <type> <name>
										 6                          replicaset     name-replicaset

autoscaling replicas based on load

to get all the running pod of a specific RS, run the following:
kubectl get rs // get all running RS
kubectl describe rs nginx-rs // First, check which labels the ReplicaSet uses:
kubectl get pods -l app=nginx // Now list Pods
