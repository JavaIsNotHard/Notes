they are virtual IP i.e there are not process actually listening on this IP

when client pod request arrives for this IP then the iptables and IPVS rules of the node perform DNAT to translate the IP to one of the healthy pods 

The IP our ClusterIP gets depends on the CIDR address of the Service that is pre-allocated during cluster creation time 

We also have an endpoint controller 
the endpoint controller watches services and pods 
It creates an Endpoints object listing all healthy pod IPs matching the Service selector
EndpointSlices are used in modern clusters 

every pod's `/etc/resolv.conf` points to CoreDNS's ClusterIP

here is what happens internally

