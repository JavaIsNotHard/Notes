Here is a summary of what needs to happen in CSMA protocol:
- The adpater needs to obtain newtork layer datagram from the layer above and frame it and place it into the adapter buffer. 
- The adapter needs to sense the channel, if there is no signal energy from the channel then it needs to transmit the frame into the channel. If there is signal energy from the channel then it needs to wait before it transmits the frame into the channel. 
- While transmitting, the adapter needs to monitor the channel to check if there are any signal energy coming from the channel. 
- If the adapter sends a frame without any collision then the transmission was successful if not then i.e if there was a collision then it needs to abort the transmission and retry after a certain interval
