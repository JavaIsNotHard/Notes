writing robust microservice includes the following topics 
- right-sized
	- responsibility of a single microservice should be considered
	- making sure a single microservice does not perform a lot of tasks 
- location transparent 
	- managing physical location of the service such that we can add instances and remove instances without impacting performance 
- repeatable 
	- when new services instance are added then we need to make sure that all the properly configuration and code are replicated between the new instances 
- resilient
- scalable

microservice patterns include 
- core development pattern 
	- single granularity  
		- what is the right level of responsibility for each service 
		- making the service too coarse-grained vs too fine-grained and their problems each
	- communication protocol 
		- how do services communicate with each other
		- or how does a service and a client communicate with each other
	- interface design 
		- how does a client interact with the service 
	- configuration management service 
		- how the service manages application-specific configuration so that the code and configuration are different
	- event processing between service
		- how to use events to communicate state and data change info between services
- microservice routing pattern
	- this deals with how the client that wants to consume the microservice discovers the location of the service and is routed over it 
	- since different services are hosted in different servers and each server will have it sown physical IP address, there must be a to abstract away all those IP addresses into a single IP address and have a single point of entry
	- service discovery 
		- locating and connecting to microservice instance without hardcoding their network addresses
		- two types of service discovery
			- client side 
				- the client looks up a service registry (the service has to first register itself into the service registry) and based on the response, the client will send the corresponding request
			- server side
				- the client sends request to a load balancer which queries the service registry and routes the request accordingly
	- service routing
		- gives client a single logical URL to talk to
		- provides services such as authentication, authorization and other business policy related stuff
		- uses an API gateway
- microservice client resilience pattern
	- client-side load balancing 
		- cache location of service instances provided by the service discovery
		- multiple calls to instances of microservice are load balanced to all healthy microservices instances
	- circuit breaker pattern
		- prevents a client from continuing to call a service that is failing 
		- failing services consume resources so we want failing services to fail fast
	- fallback pattern 
		- when a service does fail, is there an alternative path that a client can take to retrieve data from or take action with 
	- bulkhead pattern
		- makes sure that one misbehaving service does not take up all the resources on the client
- microservice security pattern 
	- authentication
	- authorization
	- credential management
- microservice logging and tracing pattern 
	- log correlation 
		- each microservice is going to produce a separate log 
		- implement a correlation ID, an unique ID that will be carried across all the service calls 
	- log aggregation 
		- pull together all the logs produced by the services into a single queryable database 
	- microservice tracing
		- visualize the flow of client transaction across all services 


- building a successful microservice architecture 
	- involves incorporating the perspective of multiple individuals within your software development organization 
		- the architect : how an application can be decomposed into individual microservices and how the microservices will interact to deliver a solution
		- the software developer : how the language of choice be used to deliver a solution
		- the devops engineer : how services are deployed and managed 
- the architect 
	- decomposing the business problem 
	- establishing service granularity 
	- defining service interface 
- the devops engineer 
	- operational lifecycle steps
		- service assembly : package and deploy the source code into an single artifact 