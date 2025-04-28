distributed caching servers
if the resource is not cached in the CDN server then it fetches it from the origin server 
AWS cloudFront and Akamai are well known CDNs

## Overlay Network
the network uses BGP protocol for routing request which uses the number of hops as a cost measurement on which path to choose 
this does not consider their latencies or congestion

CDN is a [[overlay network]] that uses variety of techniques to reduce the response time of network requests and increase the bandwidth of data transfers

CDN clusters are placed in multiple geographical location to be closer to the clients
but how do the client know which cluster is the closed to them?
using global DNS load balancing -> considers the location of the client inferred from its IP address and then lists all the geographically closed clusters taking into account also the network congestion and cluster health

they are also placed at internet exchange points where ISP connects because all network traffic are routed through this communication path between ISP to ISP.
they are placed strategically such that the client and the origin server are somehow closer to each other due to the CDN being closer in distance between them 

uses TCP optimization techniques such as pooling persistent connection and using optimal TCP window size


## Caching
