key value store 
stores the following information

nodes
pods
configs
secrets
accounts 
roles 
bindings and others

to list all the keys stored in the pod we use the following command
`kubectl exec etcd-master -n kube-system etcdctl get / --prefix -keys-only`

