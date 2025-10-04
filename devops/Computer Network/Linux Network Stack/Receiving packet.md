The high level path a packet takes from arrival to socket receive buffer is as follows:

1. Driver is loaded and initialized 
2. Packet arrives at the NIC from the network.
3. Packet is copied (via DMA) to a [[ring buffer]] in kernel memory.
4. Hardware interrupt is generated to let the system know a packet is in memory.
5. Driver calls into [[NAPI]] to start a poll loop if one was not running already.
6. [[ksoftirqd]] processes run on each CPU on the system. They are registered at boot time. The [[ksoftirqd]] processes pull packets off the ring buffer by calling the NAPI `poll` function that the device driver registered during initialization