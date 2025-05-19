broadcasting means sending a single message from one client to multiple clients in the group or in the same network
we can achieve broadcasting of message by either relying on the network hardware support such as IP multicasting and broadcasting or build additional feature support on top of the default unicast network 
the broadcast protocol should be fault tolerant i.e if one node of the group fails then it shouldn't hamper the performance or activity of other nodes
broadcast protocol use the best effort system mode which doesn't guarantee that message will be delivered to the recipent but we can create this guarantee by adding retries and retransmissions in application layer. also there is no upper bound in message latency which means that message can take any amount of time and we do not block a sender to receive acknowledgement from the receivers which means we will use asynchronous communication link 

### sending and receiving a message vs broadcasting a message

 broadcasting and delivering a message uses sending and receiving a message but we have a different abstraction layer which receives the message to send and receive which is called the broadcast algorithm. The broadcast algorithm picks up all the messages that the user broadcasts and sends it over the network and the receiving side, the algorithm picks up the message network and delivers it to the application above it. The broadcast algorithm can also buffer/queue the message before delivering the message to the application as well 

### Different forms of reliable broadcast protocol 

for reliability, we need a mechanism for retransmission prebuild that the broadcast algorithm can use
different broadcast protocol based on the order messages are delivered 

1. FIFO broadcast
	if two messages are broadcasted by the same node then all other nodes will deliver the message in the same order as they were broadcast but there is not guarantee about the order of messages that are broadcasted by different nodes. Suppose client A sends messages m1 and m3 and client B sends message m2. Then there is a order m1 -> m3 for all the nodes that received the broadcast message by the client A. But since m2 was not broadcasted by client A but rather by client B, the ordering is not fixed and can be anything between (m2, m1, m3), (m1, m2, m3) and (m1, m3, m2). Notice in all 3 ordering, m1 -> m3 is maintained.
	 
2. Casual broadcast 
	applies the happens-before and casual relationship between events. This means that if two events have a happens before relationship then the ordering should maintain this relationship between nodes. For example, client A sends m1 to client B and C, client B sends m2 to client A and C after receiving the m1 from client A. this means that m1 -> m2 is valid which means this ordering m1 -> m2 should be maintained between all ordering of the message. Suppose at the same time client B sends m2 to both A and C, client C itself sends m3 to client A and B. Here m1 -> m3 because both client A and B are local nodes but client B and C are concurrent with each other because they don't have any happens before relation which means the order of messages m2 and m3 is not guaranteed and can be applied in any order including (m1, m3, m2) or (m1, m2, m3)
	
3. Total order broadcast 

4. FIFO-total order broadcast