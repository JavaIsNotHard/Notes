- in case of log based broker, the most used approach is buffering with a large sized buffer 
- if a consumer falls behind so much that the messages that it needs are so old that it is not retained in disk then it cannot read those messages.
- this means that the broker starts to drop messages from the buffer when it exceeds the size of buffer 

- even if a consumer lags behind significantly than the producer, it only affects that consumer and no other 

- in traditional message brokers, each consumer is assigned a queue that buffers messages. these queues are mainly kept in memory and hence they are bounded by size i.e the size of the memory. if the consumer crashes then the queue starts to accumulate a lot messages in its memory indefinitely which will affect the overall performance of the system. so instead we should actively monitor the queue and the consumer status and delete the queue for those consumer which has been shutdown or are unreachable