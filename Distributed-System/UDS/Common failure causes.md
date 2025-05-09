## Network faults 

Slow network calls are silent killers of distributed system because the client doesn't know whether it will get a response eventually or not

## Resource leaks

memory is not the only resource that can leak, threads can also leak 
suppose you are sending a synchronous HTTP request to a remote server and so you create a thread pool for it
you assign a thread to perform that operation but the remote server never returns anything making the thread wait for the remote server indefinitely 

we could use asynchronous request to the remote but underneath the asynchronous request, HTTP has to maintain a TCP connection pool which so even though the application program or the application thread itself doesn't wait for the remote server to respond the TCP connection will be occupied indeifintely and if multiple such connections are created and it reaches a threshold then we are now dealing with socket leaks

the best solution to this problem is to use network timeouts

## Cascading Failures

The type of failure which is caused when one system fails and this affects and fails the other system as well 
cascading failures are common when machines are tightly dependent on one other
suppose we have two database servers running behind a load balancer that servers 50 transactions per second. Suppose that replica B becomes unavailable due to network failure in the system hence it can no longer serve request. This makes replica A handle all the request of itself as well as B because the load balancer removed the failing replica B and now sends all the request destined to B to A. This can cause replica A to fail, in other words we can say that the network failure that caused replica B to fail cascadingly caused replica A to fail as well 


## Managing Risk 

failures are inevitable in distributed systems and we must be prepared to detect, react and repair the failure
just because something is failing doesn't mean we have to do something about it 
we need to consider probability it will manifest and the impact it will cause to the system’s users when it does fail and get a risk score which helps to prioritize which faults to address first 


