filtering pods by labels 

```
kubectl get pods -l app=nginx
```

get all pods with their labels

```
kubectl get pods --show-labels
```

manually scheduling pods to a specific node

```
apiVersion:
kind:
metadata:

spec:
	nodeName: <node_name> // where we enter the value of the node where we want to schedule our pod at
```


to view labels applied to the nodes:

```
kubectl get node node01 -o json | jq '.metadata.labels'
```


