- all the frames are of size L bits
- a time slot is equal to L/R seconds i.e suppose we have a frame size of 20 bits and a sending rate (R) of 10 bits per second then the total time slot for a frame is going to be equal to 20/10 seconds = 2 seconds for each frame i.e the total time required to transmit a single frame
- Nodes only transmit at the beginning of the each time slot.
- The nodes are synchronized such that each node knows when the slot begins
- If two or more frames collide then the collision is detected before the end of the slot.

Nodes do not wait for a certain delay but rather immediately retransmits with a probability of p. This is like tossing a coin. If the event of the coin toss is head then it retransmits in the next time slot, if the event is tail then it does not retransmits in the current slot but at the next slot again.