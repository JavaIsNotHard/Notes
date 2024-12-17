- consumer group tracks consumer offset
- the consumer node keeps track of the current offset of message that it is currently processing
- all messages with offset less than the current offset has been processed by the consumer and any offset greater than the current offset have not been seen yet
- this means the broker does not need to keep track of the acknowledgement of all messages but rather periodically record the offset of the consumer 

- the consumer offset also works like log sequence number used in replication of database 
- if a consumer node is down and another node is assigned to that partition then it can look at the consumer offset to determine which messages to start processing
- 