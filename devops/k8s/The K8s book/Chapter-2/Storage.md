
we have the following components in kubernetes storage:
1. storage provider : can be either external or on premise systems
2. CSI plugin : storage interface 
3. persistent volume subsystem


CSI previously used to have in tree volume plugins which basically made the storage driver code to be included in the kubernetes source code which means that changes do the storage driver code would have to be done through compiling the entire source code of kubernetes

![[Screenshot 2025-06-19 at 10.45.59 AM.png]]

the pod on the far right needs a storage allocate to t about 50gb of disk space
the pod makes the disk space request to PVC which asks the SC to create a new PV and associated volume in the AWS backend

Persistent volume subsystem
PV is metadata + access configuration