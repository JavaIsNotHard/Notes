We already know that communication between processes over the network happens using the exchange of [[messages]]. When a sending process sends a message to a receiving process, the message first goes through a software interface called [[socket]]. 
We can take an analogy of process as a house and sockets as its door. If something needs to get out of the house then it needs to go through the door. Similarly when a message is send through the network, the message is pushed out of the door.
Here the process assumes that there is a network infrastructure that will transport the message from the source to the destination.
Once the message arrives at the destination, the message first needs to pass through the socket of the destination before acting on the message.
