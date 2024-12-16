- an approach to notify the [[consumer]] about new event 
- so the producer sends the event to the messaging system which is then pushed to the [[consumer]]
- a unix pipeline and TCP connection is an example of such. messaging system where a process can send data into these connection or pipeline and expect the [[consumer]] to receive the data 
- this approach is flawed in the sense that only one process and send data to another process at a time inside a connection

- approaches for implementing message system
- what happens if the [[producer]] produces message faster than the [[consumer]] can consume the message
	- backpressure is the most used technique to resolve this problem where the system limits the amount of events that the producer produces or stops the producer from producing any message until the event queue is not clogged with events
	- there is also the problem 


[[direct messaging from producers to consumers]]