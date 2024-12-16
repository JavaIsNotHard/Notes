- consumers can crash before or during processing a message 
- in a load balancing approach only one consumer gets the message to process and if the [[consumer]] crashes then [[event]] or message is going to get lost 
- to prevent message loss we use acknowledgement and redelivery mechanisms
- when the client has finished processing the message then it can send an acknowledgement back to the broker to let them know and remove the message from the broker's queue
- if acknowledgement is not received within a time frame then the broker assumes that the message was not processed and therefore delivers the message to another consumer 

- using the load balancing approach, the ordering of message processing is not guaranteed by the consumer
- ![[Screenshot 2024-12-16 at 1.04.43 PM.png|600]]
- here the ordering of the processing is m4, m3 and m5 because m3 crashed and the load balancing algorithm chose consumer 1 to process the message again
- if the messages are independent of one other than this is not a problem but if the ordering matters then we should use separate queue for each consumer i.e not use load balancing approach

- it can also happen that the consumer fully processed the message but failed to send an acknowledgement due to network issues
- this problem can be solved by using atomic commit protocol 
