
A downstream service is a service that dependents on the previous service for operating properly
it is the service that receives the call from the upstream service to perform an action

## Timeout

So how do we determine a good timeout interval?
one way is to use a false timeout randomly. what are the cons?
if we set the timeout too aggressively then the upstream service may timeout just before the server was about to send the response back which creates a unnecessary failure of network call 
another way to set the timeout is dynamically based on the response time of the downstream service. How?
This depends on how many request are you willing to be cut prematurely. if it is 0.1% i.e you are ok with 1 in 1000 request being cut prematurely then we can look at the response time distribution of the request and calculate the 99.9 the percentile of the response time i.e 0.1% of the time
we measure it something like this
50th percentile (median) = 100 ms 
90th percentile = 200 ms 
99th percentile = 300 ms
99.9th percentile = 500 ms 

since the response time in 99.9th percentile is 500 ms we can set the timeout interval to be 500 ms because that would mean we are allowing 1 in 1000 request to be cut prematurely
this also means that only 0.1% of the calls take longer than that

another way to implement the timeout is to implement it outside the application program and move the responsibility to a reverse proxy like the [[service mesh]] pattern where each service had its own load balancer or reverse proxy located in the same process. Why?
we can offload the responsibility of timeout and monitoring request to a separate service

## Retry

what to do after the service fails or timeouts?
we can either fail fast such that it doesn't affect the overall operation or we can retry the request again
retrying the request for a short-lived connection after some backoff time has a high probability of succeeding. but if the downstream service is already overwhelmed by large request then retrying will only worsen the situation. 

this is why we need to choose our backoff interval properly we need to slow the retry interval until a maximum number of retries is reached or enough time has passed between the request. 

this is where exponential backoff comes into play. here the delay is derived by multiplying the initial backoff duration by a constant that increases exponentially after each attempt
the delay is calculated as follows
`delay = min(capped time, initial-backoff * 2^retry number)`
if the delay value equals the capped timeout then it will never exceed that value since we are taking the minimum between the two values here

but this creates another problem. since delays are calculated using the same formula in all services, we can have multiple service retry at the same interval causing an already degraded service to degrade faster. so we need to introduce a random such that the delay value is different between the two service 

another way to implement retires is to use a retry queue in a batch processing system. another process can then read from the same queue later and retry the failed request

just because we can retry the request doesn't mean that we should. some request are inherently going to return failure whatever the delay be because it could be that the user doesn't have the authority to create such request and other stuff. here instead of retrying the request we must fail fast cancel the request right away. Also we need to understand the consequence of retrying in network call that isn't idempotent and which can affect the application's state


## Retry amplification

happens when the retries increase the load of a downstream service which is already degraded, making the problem worse 

what happens if we have a chain of request, which looks something like this
client -> request A -> requests B -> requests C

suppose the service C is degraded due to some internal problems which means service B has to wait longer for service C to complete
meanwhile since service A is also waiting for service B, it also has to wait longer and the same goes for the client as well
now suppose client, service A and service B all timeout due to service C unavailability and they all retry then the following happnes
- for a single request, 3 retry request (one from the client, one from service A and one from service B) is send to service C
- here service C is already failing but now we are getting 3x the load than before making the service C fail faster



## Circuit Breaker 

transient failures -> short lived failures that can be resolved itself
they are best handled using retries and delays
but circuit breaker pattern are used for failures that are non-transient i.e not temporary
this pattern deals with stopping requesting to the degrading server all together 
here we are not failing the entire system but rather a sub-system which the overall system doesn't depend for it to function hence failing of this subsystem shouldn't impact the overall system 
circuit breaker pattern is useful when the expectation is that the next call will fail 

the circuit breaker pattern has three states
1. open 
2. closed 
3. half open

the circuit breaker starts in the closed state where it does nothing and just monitors the number of failures and errors returned. if the number goes above a threshold then the circuit breaker trips and moves to the open state

in the open state network calls are attempted and failed immediately

after some time the circuit breaker gives the down stream service another chance and changes its state to half open where the next call is allowed to pass. if the next call returned an error then it returns to the open state and starts blocking calls again else if the operation was normal then it is moved to open state 

there are various design decisions that we need to make about the circuit breaker pattern such as the number of failures to consider before considering the downstream service as failed or how long should the circuit breaker wait to transition from open to half open state 

this decision should be made based on past failures
