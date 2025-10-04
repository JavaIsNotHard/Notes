The location and extent of queueing (either at the input port queues or the output port queues) will depend on the traffic load, the relative speed of the switching fabric, and the line speed

 as these queues grow large, the router’s memory can eventually be exhausted and packet loss will occur when no memory is available to store arriving packets

packets are “lost within the network” or “dropped at a router.” It is here, at these queues within a router, where such packets are actually dropped and lost

let Rline = input and output link's line rate
Rswitch = rate at which switch fabric can move packets from input → output

If Rswitch=Rline: the fabric can only move 1 packet per time slot → backlog at inputs.
If Rswitch=N⋅Rline​: the fabric can keep up with **the worst possible input load** → negligible input queuing.