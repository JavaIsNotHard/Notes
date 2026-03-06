example pod specification yaml file
```
apiVersion: v1
kind: Pod
metadata:
  name: random-pod
  labels:
    app: something
    type: something
spec:
  containers:
    - image: nginx
      name: nginx     
```

this creates a single Pod in the default namespace running the nginx image inside it

the READY column when running `kubectl get pods` command tells us the number of containers running inside the Pod, such as 1/1 or 1/2 which means only 1 out of 2 containers are running

you don't restart a pod but rather restart a deployment


```bash
kubectl run -it --rm mongo-client --image=mongo:6.0 --restart=Never -- bash
```

creating a temporary pod that exits after we exit from the pod