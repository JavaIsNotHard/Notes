when you set up a TCP connection, you associate a set of timers
When the keepalive timer reaches zero, you send your peer a keepalive probe packet with no data in it and the ACK flag turned on.
you will receive a reply from the remote host (which doesn't need to support keepalive at all, just TCP/IP), with no data and the ACK set.
If you receive a reply to your keepalive probe, you can assert that the connection is still up and running without worrying about the user-level implementation.

- checking for dead peers
- preventing disconnection due to network inactivity

### checking for dead peers

we have scenario where we have 2 communicating peers A and B, they have completed the 3 way handshake and have created a TCP connection between them 
now we unplug the power supply from B which will instantenously make the B to go down without sending anything over the network to notify A that the connection is broken 
A knows that there is a connection between itself and B but this is not known by B
he situation resolves itself when A tries to send data to B over the dead connection, and B replies with an RST packet, causing A to finally to close the connection

