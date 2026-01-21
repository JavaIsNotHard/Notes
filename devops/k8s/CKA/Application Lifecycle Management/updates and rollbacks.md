
rollouts and versioning in a deployment

when we create a new deployment it triggers a new rollout
a new rollout creates a new deployment revision

when the container version in upgraded then a new rollout is triggered which creates a new deployment revision

helps us rollback to a previous versions

```
 kubectl rollout status deployment/deployment
```

the above command checks the progress or status of a rollout (update) for kubernetes deployment

```
kubectl rollout history deployment/<deployment_name>
```

this command shows the revision history of the deployment

### Deployment strategy

recreate strategy
scales down the entire replicaset to 0 and then scales up the same number of replica set as before. **causes application downtime**

rolling update strategy (default)
creates a separate replica set with the new pod version, as pods are scaled one at a time, the pods from the old replica set are scaled down simultaneously. **no application downtime**

how to update a deployment??
we can change the labels, container version and more
first we change the deployment yaml file
then we apply the deployment yaml file

when we upgrade to a version of a deployment, the replica set of the previous version are not deleted in case of a rollback

```
kubectl rollback undo deployment/deployment
```
