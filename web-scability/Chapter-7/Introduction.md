**Synchronous processing**
The caller to the service or a function waits for the response before continuing its execution 

**Asynchronous processing** 
The caller never waits idle for response from service it depends on. The caller calls the service and continues its execution without getting blocked.


In a mail server system which is synchronous, when the service calls the email service the client has to wait for the service to send the mail to a remote server. This wait causes is called blocking since the client are not able to do anything else. 

In an asynchronous environment, a client request that requires a lot of time or process is placed on a message queue and the execution continues without the client having to wait. In the background, request is consumes by a backend process and the actual client request is processed here. 

We can have independent threads where the client code runs in a separate thread and the message consumer runs in a separate threads which enables parallel execution of these threads. 

Another method is to use callback where the result of the SMTP request is notified to the client code once the 

From scalability point of view, the main difference between these two approaches is that more agents (processes, threads or independent systems) can work in parallel at any point in time which also means that you can execute each agent on a separate CPU or even on a separate server.

## Message Queues
A component that buffers and distributes asynchronous requests. 
Messages are assumes to be one-way, fire and forget requests. 
Messages are produces by the message producers and then buffered by the message queue. 
They are then delivered to the message consumers who perform the asynchronous action 

They run in a separate process or a separate execution thread. 
Producers and consumers are hosted on different servers and can be implemented using different technologies 

The separation of producers and consumers gives us the benefit of nonblocking communication between the consumer and producer. 

### Message producers 
Part of the client code that initiate the asynchornous processing 
The producers have a little responsible which includes sending a valid data to the message queue 
Different consumers publish message which gets queued up in the message queue .
The producers do not have to wait for the action to complete, but can assume that the action will be completed later in time. 


### Message broker 
A specialized application designed for fast and flexible message queuing, routing and delivery
Brokers are the more sophisticated way to implementing a message queue 
They are referred to as message-oriented middleware 
The main responsibility of the queue is to be available all the time for the producer and to accept their messages and also buffer message for the consumer to consume the relevant message 

### Message consumers 
They are responsible for consuming the message from the queue and performing the asynchornonus operation 
To achieve high level of decoupling, consumers should not know anything about producers. 
Consumers are deployed on separate servers to scale them independently. There are two appraoches of implemeting consumers
- cron-like 
- daemon-like 
In cron like The consumer connects periodically to the queue and checks the status of the queue. This is a pull model because the consumer pulls message from the queue 
The daemon like the consumer run constantly in an infinite loop and has a permanent connection to the message broker. This is a push model because the queue pushes the message to the consumer.

### Message routing methods 
1. **Direct Worker Queue Method** 
2. **Publish/subscribe method**
3. **Custom routing rules method** 

#### Direct worker queue method 
Each message produced is added to a single queue. 
The queue is located by name, and multiple producers can publish it at the same time
Can have more than one consumers competing for message 
Each message is routed to only one consumer 

Distribution of time consuming tasks across multiple worker machines 
If the consumers are stateless then we can scale the architecture by adding more clones of the consumer in the system 

#### Publish/subscribe method 
Single message can be delievered to more than one consumer 
This method has topics not queues 
messages arriving to a topic are cloned for each consumer that has a declared subscription to that topic
The consumer model have to connect to the message borker and declare which topics they are interested in 
Different consumer subscribe to different message topics 
Each consumer has their own message queue and each consumer are going to be subscribed to different topic

#### Custom routing rules 
consumer can decide in a more flexible way what messages should be routed to its queue. 

### Messaging protocols 
how client library connects to a message broker and how messages are transmitted 
Most common protocols in open-source world includes AMQP, STOMP and JMS

Advanced message queuing protocol 


## Benefits of message queue
- **Enabling asynchornous processing**
- **Easier scalability** 
- **Evening out traffic spikes** 
- **Isolating failures and self-healing**
- **Decoupling**
### Enabling asynchronous processing 
- The only requirement is that you have to find a way to continue execution without having the result of the slow operation. 

### Easier scalability 
- Publish requests from mutliple servers in parallel
- Process messages in parallel on multiple back-end servers 
- Parallel back-end processing for resizing images and videos 
	- front-end uploads file to a network attached storage
	- front-end publishes the message for each file to be processed 
	- Messages gets buffered in the queue and gets picked up from the queue by the consumer i.e back-end server 
	- Once the processing is done then the result is published back to the network attached storage 
- By adding more message consumers, we can increase the overall throughput.
- Even if you use Nodejs or Erlang, which are asynchronous by nature, you would still benefit from using queues as a way to share worload among multiple servers 

### Evening out traffic spikes 
- If there is a 


## Message queue - related challenges 
### no message ordering 
- the message ordering is not guaranteed. 
- caused by the fact that messages are processed in parallel and there is no sycnhronization between consumers 
- ways to solve the ordering problem:
	- limit the number of consumers to a single thread per queue 
	- 