
Storage in kubernetes

what is storage class in kubernetes

Without a StorageClass, if a developer needs storage, they have to manually ask an administrator to carve out a piece of a hard drive (a PersistentVolume) for them

Think of the storage process like a restaurant:
- **StorageClass:** The **Menu**. It defines what types of "dishes" (storage) are available (e.g., Fast SSD, Cheap HDD).
    
- **PersistentVolumeClaim (PVC):** The **Order**. This is when a user says, "I'd like 10GB of the Fast SSD, please."

- **PersistentVolume (PV):** The **Meal**. This is the actual storage disk that gets created and delivered to the user's table (the Pod).


This all can be summarized as dynamic provisioning

Key Fields to Know
- Provisioner -> This tells Kubernetes which "plugin" to use to create the storage (e.g., AWS EBS, Google Cloud Persistent Disk, Azure Disk, or Ceph).
- Reclaim Policy -> 
	- `Delete`: When you delete your claim, the physical disk is destroyed.
	- `Retain`: When you delete your claim, the physical disk stays alive so you can recover data manually.
- AllowVolumeExpansion -> If set to `true`, you can literally "resize" your disk while it's still being used.


when setting new storage after setting up a cluster with kkubeadm, we need to consider the following things:
1. we need a local provisioner setup which will create PVs for us
2. if we don't use a provisioner and set the provisioner value to  **k8s.storage.io/no-provisioner**, then we need to manually create PVs first and only then can we create claims

