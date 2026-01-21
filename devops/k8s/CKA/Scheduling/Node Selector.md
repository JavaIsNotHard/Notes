
using node labels

to label a node we use the command: 
```
kubectl label node <node-name> <key>=<value>
```

we then make sure that the pod gets scheduled on this node by using node Selector in the yaml description as follows

limitations of node selector:
1. only exact match, no operators like In, NotIn, Exists, ranges or expressions. `disktype IN (ssd, nvme) | name NotIN (A, B)`
2. no OR logic: all labels are ANDed
```
nodeSelector:
  gpu: "true"
  high-mem: "true"
```

here gpu and high-mem are ANDed, we cannot express “node A **or** node B”, “gpu **or** high-mem nodes”
3. hard requirements only
	- If **no node matches**, pod stays **Pending**
	- No soft / preferred behavior
4. no prioritizing or weighting: Scheduler treats all matching nodes equally
5. No exclusion logic: cannot say Schedule anywhere **except** these nodes. `disktype != hdd`

