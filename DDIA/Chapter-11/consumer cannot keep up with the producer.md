- in case of log based broker, the most used approach is buffering with a large sized buffer 
- if a consumer falls behind so much that the messages that it needs are so old that it is not retained in disk then it cannot read those messages.
- this means that the broker starts to drop messages from the buffer when it exceeds the size of buffer 

- even if a consumer lags behind significantly than the producer, it only affects that consumer and no other 