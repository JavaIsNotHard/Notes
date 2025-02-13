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

## Apache kafka broker
- each broker has a kafka process running in it 
- each broker also has a local storage for persistence 
- all brokers are networked together and act as a single kafka cluster 
- retention time is the time that the broker will keep the events in the local storage 
- so kafka cluster is basically a collection brokers 

- along with producers, consumers and the kafka cluster, apache kafka also contains something called as Zookeeper which is basically used for consensus among the brokers to agree on whether something is true 

- producers and consumers are decoupled from one other 
- slow consumers do not affect the production rate of the producers 
- we can add new producers without affecting the consumers 
- failure of a single unit does not affect the other unit 

- topic is a stream of related messages 
- also can be thought of as sequence or log of events 
- there can be unlimited no topics theoretically

- allocate different brokers to individual topic partition (this is done for scalability because only scaling a single topic is hard)
- new messages are placed at the end of the partition since each message is immutable piece of data 
- ordering is guaranteed using partitioning
- each topic is partitioned into different physical brokers to enhance parallelization (because now we can compute events in a single topic in different machines at the same time)
- kafka cluster decides where the partition for a topic are going to live 
- the kafka cluster does not assign new broker if a broker is down or determine the size of the broker 

- brokers manage partition
- each partition is stored on broker's disk 
- partitions are replicated in different brokers for availability 
- one replica is called the leader and the other are called follower 
- producers are producing to the leader broker 

- how does kafka producers assign messages to producers 
- if the msg has no key then round robin method is used 
- if it contains a key then hash(key) % no of partition is used to compute the dest partition
- same key will always land on the same partition until the no of partition remain constant, this ensures ordering of messages 

- consumer keeps track of consumer offset to ask for the msg after consuming all the previous messages in a topic called consumer offset topic 

- writing to log will make the log run out of space eventually
- for this problem the log is divided into segments like in LSM trees where duplicated records are removed during compaction and merged together after some time with other segments 