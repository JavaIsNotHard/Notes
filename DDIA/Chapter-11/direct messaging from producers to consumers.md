- using UDP multicasting 
- using brokerless messaging libraries such as ZeroMQ 
- making the consumer expose a service which the producer can send either http or rpc request to 

- all these approaches work well when both the producers and consumers are online, if the consumer are down when the event is produced then the event is going to get lost 
- so instead a better approach is to use [[message broker]]