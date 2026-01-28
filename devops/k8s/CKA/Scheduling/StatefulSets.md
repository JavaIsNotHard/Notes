used for applications that require their state to persistent throughout the lifecycle of the pod i.e even after the application is down and requires a restart

statefulsets give a stable network identities, persistent storage and ordered deployment/scaling

### what does ordered deployment mean?? and why is it needed??

in ordered deployment the replicaset are scaled one at a time rather than all at once or multiple replicas simulatenously

use cases of statefulset
1. database replication setup
	1. suppose we have 2 replica pods and a primary pod
	2. without statefulset the replica pods may start before the primary pod and tries to read replication data from primary but primary is not available yet
	3. if we use statefulset then we can allow the primary pod to start before the replica pod can read the replication log from the primary


uses bindingMode : WaitForFirstCustomer to delay binding until a pod using it is created

has a headless service which provides individual pod DNS : `mysql-0.mysql`, `mysql-1.mysql`, `mysql-2.mysql`

we can have both. headless service and a cluster IP type service for statefulsets

each pod/statefulset gets its own persistent volume claim which enables persistent volumes in the kubernetes cluster

rolling updates happen in reverse ordinal order, and each pod must be running or in READY state before the next pod can start 

each pod are named in ordinal order such as <pod_name>.0, <pod_name>.1 and so on

### Limitations

- deleting or scaling a statefulset down will not delete its associated volumes

statefulsets has a feature called volumeClaimTemplates that automatically creates a PVC for each pod 


