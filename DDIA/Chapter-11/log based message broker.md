- combination of both persistent databases and message brokers
- persistent database can read input files from and past and produce the same result while message brokers can only process inputs given in the current time and cannot process any past inputs
- if we add a new consumer then it will only starts receiving messages sent after the time it was registered; any prior messages are lost and cannot be received by the new consumer
- but in databases and filesystems, we can add new client and read data item written in the past 
- batch processing systems do not affect the input given to it i.e it processes the input as read-only whereas messaging systems have the tendencies of deleting messages after using it or after acknowledgement

- so why not combine the durable storage approach of database with the low-latency notification facilities of messaging system. this is the idea of log based message broker
- 