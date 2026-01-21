advanced scheduling constraint
allows you to control which nodes your pods can be scheduled on based on node labels

why node affinity over [[Node Selector]]??
- Supports complex logical operators

types of node affinity:
1. **requiredDuringSchedulingIgnoredDuringExecution** (Hard Requirement)
2. **preferredDuringSchedulingIgnoredDuringExecution** (Soft Preference)

- during scheduling : rules are applied when pods are being scheduled
- during execution : rules are applied to already running pods
- required : must match
- preferred : try to match

Type 1: Required Node Affinity

```
requiredDuringSchedulingIgnoredDuringExecution
```

all pods that are to be scheduled must match its label with the node's label and only those nodes that match the labels are to be used to schedule that pod

or 
pods will be scheduled on nodes that match the labels

the format of a node affinity is as follows:
```
spec:
	affinity:
		nodeAffinity:
			requiredDuringSchedulingIgnoreDuringExecution:
				nodeSelectorTerms:
				- matchExpressions:
				  - key:
				    operator:
				    value:
				    - 
				  - key:
				    operator:
				    value: 
				    - 
				- matchExpressions:
				. - key:
				    operator:
				    value:
				    - 
				  - key:
				    operator:
				    value: 
				    - 
```

- `nodeSelectorTerms`: List of terms (OR relationship between terms)
- `matchExpressions`: List of expressions (AND relationship within a term)
- `operator`: In, NotIn, Exists, DoesNotExist, Gt, Lt
- the values in the `values` option also have OR relationship

operators:
- `IN` -> Label value must be in the list  -> `disktype In [ssd, nvme]`
- `NotIn` -> Label value must NOT be in the list -> `disktype NotIn [hdd]`
- `Exists` -> Label key must exist (value doesn't matter) -> `gpu Exists`
- `DoesNotExist` -> Label key must NOT exist -> `spot-instance DoesNotExist`
- `Gt` -> Numeric comparison: greater than -> `cpu-cores Gt 8`
- `Lt` -> Numeric comparison: less than -> `memory-gb Lt 32`


```yaml
apiVersion: v1
kind: Pod
metadata:
  name: database-pod
spec:
  affinity:
    nodeAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        nodeSelectorTerms:
        - matchExpressions:
          - key: disktype
            operator: In
            values:
            - ssd
            - nvme
          - key: environment
            operator: In
            values:
            - production
  containers:
  - name: postgres
    image: postgres:14
```