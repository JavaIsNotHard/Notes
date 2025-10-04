takes segment from the transport protocol, encapsulates them in a datagram and sends it over the internet or to its nearby router

the network layer has two main components, which includes
1. [[control plane]]
2. [[data plane]]

every router has a forwarding table associated with it 
the routing algorithm in each router determines the value of the forwarding table
traditional routing algorithm computes values based on the communication between themselves and other routers
but recent development has introduced another way to do that, using something called as SDN
in the SDN approach, there is a remote controller that computes and distributed the forwarding table values to each routers 
SDN -> software defined networking

the network layer is described by the [[Internet Protocol]] (IP) which is a connectionless protocol which means each network layer datagram are handled independently 

