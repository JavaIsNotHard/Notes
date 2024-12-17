- combination of both persistent databases and message brokers
- persistent database can read input files from and past and produce the same result while message brokers can only process inputs given in the current time and cannot process any past inputs
- if we add a new consumer then it will only starts receiving messages sent after the time it was registered; any prior messages are lost and cannot be received by the new consumer
- but in databases and filesystems, we can add new client and read data item written in the past 
- batch processing systems do not affect the input given to it i.e it processes the input as read-only whereas messaging systems have the tendencies of deleting messages after using it or after acknowledgement

- so why not combine the durable storage approach of database with the low-latency notification facilities of messaging system. this is the idea of log based message broker

- A log is simply an append only sequence of record on disk 
- producer appends new message as records to the end of a log disk
- consumers read the log sequentially until it reaches the end of the log and then waits for notification that a new message has been added to the log

- to achieve higher throughput then provided by a single disk we can partition the log such that each log partition can run in different machines each independent of one other
- A topic is divided into multiple partitions that all carry messages of the same type 
- within each partition, the broker assigns a auto incrementing sequence number which acts as offset for the message 
- this sequence number is used for ordering of the message
- ![[Screenshot 2024-12-17 at 7.56.53 AM.png|600]]


[[log based compared to traditional message broker]]

[[consumer offset]]

[[disk space usage]]

[[consumer cannot keep up with the producer]]

[[replaying old messages]]