types of volumes in kubernetes:
1. emptyDir : 
	1. create a volume for the lifecycle duration of the pod
	2. created before the pod is started
2. hostPath: mount files from the worker node's filesystem
3. nfs: network file system
4. cloud volume : provisioned by cloud providers
5. configmap, secret : special type of volumes used to expose information about the pod and other kubernetes objects through files
6. persistentvolumeclaim: 
	1. integrate external storage into pods
	2. instead of directly pointing to an external storage volume point to a PVC (persistent volume claim) object that points to a persistent volume object that finally references the actual storage
7. csi


Populating an emptyDir volume with data using an init container

Understanding where the files in an emptyDir volume are stored
the directory in which emptyDir stores its file is 

```
/var/lib/kubelet/pods/<pod_UID>/volumes/kubernetse.io~empty-dir/<volume_name>
```

In emptyDir, when the pod is deleted, the volume and its contents are deleted
in other types of volumes, they don't create a new directory, but instead mount an existing external directory in the filesystem of the container



### k3s storageclass 

k3s uses the waitforfirstconsumer storageclass option which does the following
- prevents the PVC from being bound to a PV when the PVC is created, the PVC will remain in pending state
- the actual binding of the PV to the physical node only occurs when a pod that references the PVC is created and scheduled 
- essential when working with multi node cluster which makes sure that location where the pod will run is known the PVC is bound, this ensures that there are no unused PVC in the node because the pod was scheduled to another node

things to consider using this mode:
- when using waitforfirstcustomer, you must not specify the nodeName in the pod's manifest because this bypasses the kube scheduler which coordinates the volume binding which could cause the pod and PVC to be stuck in PENDING state. instead use nodeSelector


### access modes

### reclaim policy


dynamically provisioned pv created by the local-path storage class provisioner by k3s


### storage class
used for dynamic provisioning of PVCs, instead of having to manually create PVs first then create a request with PVC, storage class auto creates the PV for us when we create a PVC



if the pvc and pv are stuck in the terminating state for a long time then one of the main culprit is finalizers which prevent data loss like `kubernetes.io/pvc-protection`

or if a pod is still using that volume then kubernetes waits for that pod to release the volume

if the issue is due to finalizers, then use the following command to remove the finalizers
`kubectl patch pvc pv-claim -p '{"metadata":{"finalizers":null}}'`

or just delete the pod that was using that volume


to view if there are active pvcs, use the following command
```
kubectl describe pvc -n default | grep "Used By"
```
this outputs all the pvcs that are used by any active pods

then use the following to delete all pvc's that are not used
```
kubectl delete pvc --all -n <namespace_name>
```


how to achieve multi-node shared volume persistence ??
cannot be achieved using local-path provisioner given by k3s by default