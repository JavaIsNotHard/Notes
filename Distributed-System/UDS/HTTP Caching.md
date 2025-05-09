used for caching static resources at the client's browser 
reduces network call, reduces the load of the server and the response time 
limited to safe request methods that don't alter the server's state, like GET or HEAD
the server uses specific HTTP response headers

two types of HTTP caching
1. private caching
	- cache tied to a specific client
	- since the stored response is not shared with other clients, private cache can store personalized user data in the cache
	- private cache can be used using the HTTP header `Cache-Control: private`
	- they are usually controlled by cookie 
2. shared caching 
	- shared cache is located between the client and the server 
	- can be classified as a proxy cache
	- `Cache-Control: no-store, no-cache, max-age=0, must-revalidate, proxy-revalidate`
3. managed caching


if the resource has expired, it's considered stale
in this case the cache sends a GET request to the server with a conditional header "If-None-Match" containing the version identifier of the stale resource to check if newer version is available 
if there is a new version of the resource then the server returns the updated resource, if not, the server replies with a 304 not modified status code

ideally, the static resource should be made immutable such that they are cached forever
if static resources needs to be modified then we can create a new resource rather than modifying an existing resource and creating a new URL for it such that the client is forced to fetch it from the server

CQRS (command query responsibility segregation) pattern is used to separate the read model from the write model instead of having a single model such as CRUD for everything we can have a query model for reading and a command model for writing
now each model can perform separate read logic because in many web services read request are several orders of magnitude higher than the number of writes

## Reverse proxies 

this is used to implement shared cache mechanisms
decrease the load of the server because the cache is shared among clients,
example
if we were using a client-side cache where 1000's of user send a request for a new fresh data that was not present in the cache
since the data is not in the cache all 1000 users are going now send the request to the server which increase load on the server
instead of we used server-side caching then the first of 1000 request will be intercepted by the proxy and send to the client since the proxy does not yet have the data and for the next 999 request which be served through the proxy server

