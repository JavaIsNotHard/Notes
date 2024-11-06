When a client makes a series of request to the server, the server responds to each request one by one and sends back the appropriate response. There are two ways [[TCP]] handles multiple request serially:
- [[non-persistent connection]]: Each request/response pair has its own TCP connection associated with it.
- [[persistent connection]]: All the request/response done serially has a single TCP connection.

