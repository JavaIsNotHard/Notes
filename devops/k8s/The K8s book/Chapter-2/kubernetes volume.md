types of volume
1. emptyDir : allows pod to store data for the duration of the pod lifecycle.The directory is created just before the pod starts and is initially empty - hence the name
	1. hostPath : mount files from worker node's filesystem into the pod 
2. nfs
3. gcePersistentDisk, awsElasticBlockStore
4. configMap: Special types of volumes used to expose information about the pod and other Kubernetes objects through files. They are typically used to configure the application running in the pod
5. persistentVolumeClaim
6. CSI : Container Storage Interface

there are mainly two types of volume 
1. ephemeral  -> temporary or short term volume
2. persistent -> they are persistent for long term use



features of volumes in kubernetes
- persist file across restarts
- mounting multiple volumes in a container 
- sharing files across multiple containers 
- we can also persist volumes across pod instances
- sharing data between pods rather than between containers

volumes are typically components of pods which means that on pod restart volumes are also restarted and hence the entire data is lost


### EmptyDir

two things must be done for the changes to persist with emptyDir:
1. the EmptyDir volume must be added to the pod 
2. the volume must be mounted into the container 



