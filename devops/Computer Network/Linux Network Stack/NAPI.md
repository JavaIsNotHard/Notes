Stands for New API
It’s a **mechanism in the Linux kernel** for high-performance network packet reception.

## How it works

hybrid approach between interrupt + polling the NIC 

1. when the first packet arrives at the NIC, then it interrupts the CPU
2. then NAPI will stop all the interrupts from the NIC and put the NIC in polling mode
3. in polling mode the kernel polls the NIC for more packets rather than the NIC interrupting the kernel
4. polling continues until
	1. Either the NIC’s receive queue is empty, or
	2. A configured **quota** of packets has been processed (to avoid starving other tasks).
5. once the traffic slows down then, polling stops and interrupts are enabled again


## Why NAPI?

-  traditionally NIC used interrupt driven model where for each packet, the NIC generated interrupt for the kernel 
	- Each incoming packet triggers a **hardware interrupt**
	- The CPU stops what it’s doing, runs the interrupt handler, and processes the packet.
- At **high packet rates** (e.g., 1 million packets/sec), interrupts arrive too frequently:
	- CPU gets overwhelmed by interrupt storms.
	- Too much time spent context switching, not enough time processing packets.