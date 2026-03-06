normally we authenticate a request such as follows

```
curl https://my-kube-playground:6443/api/v1/pods \
	--key admin. key
	--cert admin.crt
	--cacert ca.crt
```

here we specify the key, certificate and the ca certificate as arguments to the request 

or like this

```
kubectl get pods
	--server my-kube-playground: 6443
	--client-key admin.key
	--client-certificate admin. crt
	--certificate-authority ca.crt
```


typing all these options for each request is tedious hence we write a KUBECONFIG file

the KUBECONFIG file contains all the authentication related options 

the kubeconfig file contains the following components
1. cluster
2. users
3. context
context maps the a cluster to a user
it tells which users are allowed to which cluster or which user uses which cluster and so on
for example, we have a dev cluster and a dev user, then we create a context such as follows in the kubeconfig file
dev@dev with the format <user_name>@<cluster_name>


