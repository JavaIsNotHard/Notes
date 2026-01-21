for a load balancer to provider a public IP for external client to connect to, the nodes that the cluster manage must also have a public IP associated with it.
if using on premise deployment then it gets difficult to make public IP of the node because there is only a single public IP provided by the ISP router to the nodes

if the cluster is running in a cloud environment then we can add the nodes in a public subnet which will be provided with a public IP for external clients to connect to.
k8s in cloud environment talk to the cloud provider's API to create an external load balancer

```
External Client
    ↓
External Load Balancer (Public IP)
    ↓
NodePort on any Node (randomly selected)
    ↓
ClusterIP (iptables rules)
    ↓
Pod IP (selected pod)
```

the load balancer keeps track of a list of healthy worker nodes to forward the traffic to
when packet arrives at the external load balancer then it forwards the request to one of the healthy nodes

the load balancer performs DNAT 
Original Packet (from client):
```
Source IP:      198.51.100.25
Source Port:    54321
Dest IP:        203.0.113.50 (Load Balancer public IP)
Dest Port:      80
```

**After Load Balancer DNAT:**
```
Source IP:      198.51.100.25 (unchanged)
Source Port:    54321 (unchanged)
Dest IP:        10.0.1.11 (Node2 private IP)
Dest Port:      32000 (NodePort)
```

The load balancer also maintains a **connection tracking table**:
```
Connection Table Entry:
┌──────────────────────────────────────────────────┐
│ Client: 198.51.100.25:54321                      │
│ LB Public: 203.0.113.50:80                       │
│ Backend: 10.0.1.11:32000                         │
│ State: ESTABLISHED                               │
│ Timeout: 300 seconds                             │
└──────────────────────────────────────────────────┘
```

packet arrives at the node's interface:
```
┌─────────────────────────────────────┐
│ Node2 Network Interface (eth0)      │
│ IP: 10.0.1.11                       │
└─────────────────────────────────────┘
         ↓
Packet arrives: 10.0.1.11:32000
         ↓
┌─────────────────────────────────────┐
│ Linux Kernel Network Stack          │
│ - Checks routing table              │
│ - Checks iptables rules             │
└─────────────────────────────────────┘
```

kube-proxy will write iptable rules associated with nodeport service for allowing traffic at the node's random port number which will forward the request to a endpoint pod

load balancer also create a [[NodePort]] service 

one of the major downside when using LoadBalancer type is that we need to create separate Load Balancer for separate service type, suppose if we have 10 different services that we need to expose to the internet then we would need 10 different Load Balancers

so instead [[ingress]] type is used