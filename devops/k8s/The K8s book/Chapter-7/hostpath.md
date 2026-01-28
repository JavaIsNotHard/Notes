hostpath works best with [[DaemonSet]]

`hostPath` lets that pod access **that node’s filesystem**

why not normal pods??
- pods can move between nodes
- hostpath is node-local meaning if the pod are rescheduled to another node than before then it no longer have access to the data in the new node

why daemonsets??
- pods run in all nodes
- which means if one pod of a daemonset is down, it can be rescheduled and continue reading from the hostpath because it is persistent in all nodes
