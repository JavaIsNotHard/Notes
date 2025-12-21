supports rolling update
rollbacks
replicas 

rolling update:
- create new pod
- gradually terminate old pod 
- keep the app available during update

rollback:
if something goes wrong then kubernetes rollsback to previous working version

A controller **only manages objects it owns**.
so this means we cannot manage pods created with ReplicaSet using Deployment even if they have the matching labels
