session affinity

if a single user sends two request to the ALB then it will forward those 2 request to the same backend server behind the load balancer

this can be enabled in application load balancer and classic load balancer

uses cookie that are sent as part of the request from the client to the server

the cookie has a expiration time which means after the cookie has expired the request will be redirect to a different instance

enabling stickiness means you are bypassing the load balancing algorithms that would normally distribute the traffic between all the servers, brings imbalances to the load