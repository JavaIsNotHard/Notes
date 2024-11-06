It is a network device which takes in packets from its incoming communication link and forwards packets from its outgoing communication link. There are mainly 2 types of commonly used packet switch which includes: [[routers]] and [[link layer switch]].

Each packet switch has multiple links attaches to it. Since packet switch needs to do both transmission and receiving action they have separate buffer to hold data.

The input buffer holds the incoming packets whereas the output buffer holds the outgoing packets. The output buffer also known as a output queue places all the packets that needs to be send to other destination system in a queue like data structure. In this buffer all the packet needs to wait for certain time before the packet switch transfers the packet. 