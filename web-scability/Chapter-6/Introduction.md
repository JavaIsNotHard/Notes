### Cache hit ratio 
The most important metric when it comes to caching 

Three main factors affecting the cache hit ration 
1. data set size 
2. space 
3. longevity 

Size of your cache key space 
Cache key is used to identify an object in the cache 
For an online store, we can use the product ID as the cache key 
The cache key space is the number of all possible cache keys that you application could generate 
A cache key for a weather forecast app based on the IP address of the client could result to 4 billion entries of cache key which is not good 
So choosing the right cache key is important 
Instead of caching based on the IP address, we could cache based on the origin country 

Number of items we can store in the cache before running out of space. 
replacing or evicting objects from the cache reduces the cache hit ratio 
The more object you can fit in the cache, the better the cache hit ratio.

How long can a object be stored in the cache before it becomes invalid.
For a weather forecast app, the TTL (time to live) of an object can be large i.e about 15 or more minutes. But for application that changes data per second, for example a live streaming platform then the TTL must be as small as possible.

The use case where the number of reads is greater than the number of writes is a good candidate for caching whereas use cases with data updating very often may render cache useless

Types of caching
1. http-based caches
2. custom object caches 

### caching  based on HTTP 
All of the caching technologies working in the HTTP layer work as read-through caches 
Read-through cache is a caching component that returns cached object if found in the cache, else it will request the main server for the object and return that to the user. Basically the client will be talking to the read-through cache rather then the main server. 

#### HTTP caching headers 
The cache-control header 
The options for cache-control header includes:
1. private  -> the result is specific to the user that requested the object and cannot be served to other users, which means that only the browser will be able to cache this object
2. public  -> The response can be shared between users as long as it has not expired
3. no-store -> The response should not be stored on the disk
4. no-cache  -> the cache needs to ask the server whether the response is still valid every time user requests the same resource.
5. max-age -> TTL of the response. is not recommend to use 
6. no-transform -> should not change the response by any mean 
7. must-revalidate -> once the response becomes stale, the response must be re validated by the origin server. This stops stale cache objects from being sent to the client

The expires header option lets you choose an absolute point in time when the object becomes stale. Can be used instead of the max-age cache-control header option

The vary header.  Tells the cache to generate multiple variations of the response based on some http request header. 
`Vary: Accept-Encoding`
return responses encoded in different ways depending on the `accept-encoding` header option. If the browser supports gzip then compress it with gzip else return an uncompressed response. 

Other caching related headers include Age, last-modified, if-modified-since and etag


### Types of HTTP cache technologies 

There are four main types of http caches 
- browser caching 
- caching proxies 
- reverse proxies 
- CDN 
Most of them do not have to be scaled manually since they are controlled by the client or by third party services. 

#### Browser caching 

#### Caching proxies 
server installed by local corporate network or ISP. Recently the use of caching proxies has been less because bandwidth has become cheaper and websites use a protection layer called SSL/TLS. Since the encryption and decryption can be done only by the origin server or their reverse proxies and cannot be done by the local network or ISP, they cannot cache the content anymore 

#### Reverse proxy 
Adding a caching server inside your data center between the client and the actual server.
The caching server or reverse proxy will satisfy the client request on behalf of the server which reduces the amount of traffic towards the origin server. 
Gives more flexibility because you can override HTTP headers and better control which requests are being cached and for how long

#### CDN
they are like caching proxies but are installed by private companies through the globe
Reduces the load of the main server
Push the content to the server that is closed to the user therefore can decrease network latency 
Use CDN to cache static files like images, css, js, videos, or pdf documents 
Generate URL for all the static files 

### Scaling HTTP caches 
browser caching and third party caching like local network or ISP cannot be scaled because they are out of reach. 
CDN auto scales based on the traffic so we do not need to do anything fancy
The only thing that we need to scale is reverse proxy if we have installed them in our data center 

It is more important to decide what to cache and for how long rather than how to scale reverse proxies 

you need to focus on the cache hit ratio. the cache hit ratio is affected by the following factors:
- cache key space: cache key is basically like a primary key by for the cache
- TTL of the cache object 
- size of the cache 

We do not need to worry about the cache becoming full and setting the TTL of cache object to a long time rather the algorithms used in the in-memory cache evict cache object based on least used objects which is the LRU algorithm

Verification that cache live in memory as long as possible and only those objects are stored which can be effectively reused then we can start thinking about scaling out our reverse proxies 

Nginx reverse proxy is considered a good choice.


## Caching application objects 
The second most important caching component after the http-based caching is custom object caching. 
Custom object caching are cache-aside rather than read-through cache

The application needs to be aware of the existence of the object cache, whereas in read-through cache the application was not aware of a component between the load balancer and the server itself.

cache-aside cache is a key-value storage. 
If the object is present in the cache then it would retrieve the cached object else it would perform necessary operation to build the object from scratch

### Common types of object caches 
#### Client side caches : 
Store the object neccessary in the client's local storage so when the client requests for a particular object and it matches with its cached object in its local storage then it would not send the request over the network and would just retrieve it from its local storage. 
This objects are stored permanently and is available even after the user restarts their device  but users can remove these caches from their device manually.
#### Caches co-located with code
Object cache that is located directly on the web server. Benefits include:
- objects are cached directly in the application memory
- objects are stored in shared memory segment so that multiple processes running on the same machine could access them

Limitation of this approach is scaling the local cache. Since the cache are not synchronized between the servers it means that multiple servers can have the same data at the same time. Suppose each server dedicated 1gb of total memory to the local cache then it would mean the total memory is only 1gb and no more. 
Another limitation of this approach is consistency of information between the servers. 

#### Distributed object caches 
Involves network round trip time which is greater than the local cache access time. 
But better in consistency and scalability 

You can scale by adding more servers to the cache cluster, by this you can scale the throughput and the overall memory pool of your cache. 
You can also remove objects from the cache allowing for cache invalidation
In distributed environment you can connect to all your cache and request object removal for data consistency 
The cache servers also use the LRU algorithm to evict object when the memory is in limit 

### Scaling object caches
client side web browser cache cannot be scaled by us. This method makes sure that you can keep adding users and do not have to scale the client-side caches to store the user-specific data. 

The web server local caches are scaled by falling back to the file system as there is no other way to distribute or grow cache that lives in single server
Since objects are accessed rarely it may be a good idea to use the local file system to store cached object as serialized files 

Distributed object caches can be scaled using data partitioning. 
open source solutions like redis and memcached are simpler and reply on client side data partitioning 

You can use reids and memcached to partition the data among multiple servers by declaring a  cluster that will cache servers using a consistent hashing algorithm. Each server in the cache cluster is assigned a hash range which says which server to communicate to when a particular hash in given.  Anytime a GET or SET is called then the cache library will hash the key and choose one of the server to store the cache. 
This layout allows for horizontal scaling of servers 

Another approach to scale object caches is to use data replication or a combination of data replication and data partitioning 
Redis allow for master-slave replication deplyment where the master servers are responsible for writes whereas the slaves are responsible for the reads. The slaves asycnhronously updates its value with respect to the master server

NOTE: cache invalidation is simply removing objects from cache once the source data changes to avoid using stale object. 
## Caching rules of thumb
