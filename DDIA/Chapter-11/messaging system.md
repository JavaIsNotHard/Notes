- an approach to notify the [[consumer]] about new event 
- so the producer sends the event to the messaging system which is then pushed to the [[consumer]]
- a unix pipeline and TCP connection is an example of such. messaging system where a process can send data into these connection or pipeline and expect the [[consumer]] to receive the data 
- this approach is flawed in the sense that only one process and send data to another process at a time inside a connection

- within the publish/subscribe model, different system takes different approaches and there is no right answer, to differentiate the system it is helpful to ask the following questions:
	- what happens if the producer produces message faster than the consumer can consume the message?
		- there are three main options which includes: dropping new messages, buffering the new messages in queue or applying backpressure (flow control) which limits the rate at which the sender sends the message until the receiver is healthy enough to accept new messages
		- another question to ask is what happens if nodes crash - are messages lost?, handling node failures requires special actions such as replication and some form of writing to disk such as log
- whether the loss of message is acceptable or not depends on the type of application

- batch processing system makes this guarantee that provide strong reliability through retrying failed tasks as well as discarded partial output from failed nodes


- approaches for implementing message system
- what happens if the [[producer]] produces message faster than the [[consumer]] can consume the message
	- backpressure is the most used technique to resolve this problem where the system limits the amount of events that the producer produces or stops the producer from producing any message until the event queue is not clogged with events
	- there is also the problem 


[[direct messaging from producers to consumers]]