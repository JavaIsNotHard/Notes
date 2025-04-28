replicate data without needing consensus

state machine replication requires two main ingredients
1. a broadcast protocol that guarantees that every replica receives the request in the same order i.e total order broadcast protocol
2. a deterministic function that handles updates on each replica

## Broadcast protocol
traditional communication over the network happens through a unicast protocol such as TCP
to deliver message to a group of processes, a broadcast protocol is needed (multicast)

types of broadcast protocol
1. best effort broadcast -> makes sure that if the sender doesn't crash, the message is delivered to all non-faulty processes. send the message one by one over a reliable link
2. reliable broadcast -> guarantees eventual deliver of message to all processes in the group. each process retransmit the message to the rest of the group. downside is this requires sending a message N^2 times 
3. the number of retransmit can be reduced by only retransmitting a message to only a random subset of process. this is called gossip broadcast protocol. this is a probabilistic protocol and doesn't guarantee that message will be delivered to all process. useful in large number of processes. doesn't guarantee the order of messages
4. the ordering of the messages is handled by total order broadcast which requires consensus

[[CRDT]]



