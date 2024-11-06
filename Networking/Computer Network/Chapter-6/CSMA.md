Carrier sensing multiple access
carrier sensing -> the node before transmitting in the channel senses the channel, if there are other node transmitting in the node then wait for a certain time before resensing
collision detection -> if a transmitting node detects that another node is transmitting in the same channel a interfering frame then it stops transmitting and waits a random time before retransmitting
The propagation delay between a sending node and a receiving node determines the performance of CSMA. Suppose node B is sending frames to a channel and before the frames can reach node D, node D senses the channel and finds it empty (since the bits of node B has not reached node D), this results in collision of bits between node B and node D
[[CSMA-CD]] is used for collision detection 
The random wait time of [[CSMA-CD]] is calculated using the [[binary exponential backoff]] algorithm