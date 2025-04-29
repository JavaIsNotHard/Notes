 for a cache to be cost-effective, the proportion of requests that can be served directly from it (hit ratio) should be high
 the hit ratio depends on several factors such as
 1. universe of cacheable objects
 2. the likelihood of accessing the same objects repeatedly
 3. the size of the cache


## Cache policies 

when a cache miss occurs, the missing object has to be requested from the origin server which can happen in two ways
1. if we get a "object not found" error from the cache, then application requests the object from the origin server and updates the cache. this is referred to as side cache
2. another approach is to make the cache itself request the origin sever when there is a cache miss and update the cache

expiration policy using TTL is a workaround for cache invalidation which is hard to implement in practice. why?
suppose we have a query that fetches a list of user based on some search criteria and this result is cached, suppose some other user updated the source of truth i.e the database without updating the cache then how is the cache to know that a single entry in its cached data has been invalid. keeping track of data is expensive

instead we could use TTL i.e Time to live which helps us to invalidate cache when a the cache entry timer times out. each entry is associated with a TTL value and when the value expires the object is removed from the cache. 
the longer the TTL, the higher the hit ratio, but also the higher likelihood of serving stale and inconsistent data

even if the cache has expired, we can still serve the object until the next time the same object is requested because if the origin server is temporarily unavailable then it's more resilient to return an object with an expired TTL to the application rather than an error

we also have LRU (least recently used) algorithm which is used to evict objects from the cache when the cache has filled up to maximum

## Local cache 

putting the cache in the client application itself
each client cache is independent on the other, the same object are duplicated across caches, wasting resources 
consistency issues will inevitably arise because two clients might see different versions of the same object
causes thundering herd effect where the downstream service is hit with a spike of request because the cache had to restart from a failure in the client side and couldn't return a cache hit

clients can reduce the impact of thundering herd effect by coalescing requests for the same object, the idea is that the if there are 5 request for the same object then the first request hits the origin server and the rest 4 clients wait for the result of the 1st request and reuse it

## external cache

client shares the same cache across requests
if 10 clients get a cache miss from its client cache then all 10 will request the origin server for the resource which causes load in the server
instead we could use external cache that shares the cache among the clients such that 10's of cache miss results to only 1 request to the origin server 

external cache can increase its throughput and size through partition and replication
this also reduces the consistency issues of client side caching because they all see a single version of the object at any given time 

external cache now needs to be scaled out if the load increases, to avoid cache miss or cache degrading we need to make sure that as little data as possible be moved around. this is achieved using consistent hashing that reduce the amount of data that needs to be shuffled when the cache is rebalanced

latency is higher because it needs a create a network request which was not needed in client side cache or local cache

the system needs  way to survive if the cache suddenly becomes unavailable

