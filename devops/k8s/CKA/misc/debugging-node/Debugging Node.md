
```
kubectl get nodes
```

to check if all nodes are registered correctly

```
kubectl cluster-info dump > dump.json
```

to redirect the cluster info to dump.json file

## Debugging a down/unreachable node

```
kubectl describe node <node-name>
```
