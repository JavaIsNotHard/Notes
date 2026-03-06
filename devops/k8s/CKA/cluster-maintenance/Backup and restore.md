
### backup candidate

resource configuration such as .yaml manifest files : store this one repos

etcd cluster

persistent volumes


backing up all the objects that are currently running in the cluster
```
kubectl get all -A -o yaml > all-deploy-services.yaml
```


 when etcd is created, it starts at a particular data-dir where all the data are stored
 we backup this directory