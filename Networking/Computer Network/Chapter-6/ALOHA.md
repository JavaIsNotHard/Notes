There are no time slots and this is the first ALOHA framework. 
There is delay between retransmission 
The network datagram when it is encapsulated into a data link layer frame then it is immediately send into the channel regardless of any time slot
Send a frame then wait for a certain timeout, if ack received for the frame within the timeout interval then successful else needs to retransmit the frame again. But before retransmission wait for a certain time interval then retransmit after the time interval until the frame is successfully transmitted with an acknowledgment 