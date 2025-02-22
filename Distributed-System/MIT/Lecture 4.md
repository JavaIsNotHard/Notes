- Replication -> fault tolerance -> high availability
- what kind of failures replication can deal with?
	- **fail stop failure of a single computer**
		- if something goes wrong then the computer stops computing and this will not compute wrong results e.g someone trips over the power cable of a server which makes the entire server unaccessible, or the network of the server is down and more 
	- **not software or hardware bugs**
		- there might be some bugs that replication can deal with 
		- for example there can be another service in the server that crashes the entire server along with the kernel without affecting any results or responses of our main service then this is a type of fail stop failure
- is replication worth it for the expense that it produces?
	- depends on the value of having a available service 


- approaches to replication
	- state transfer 
		- sent the entire state of the primary machine to the backup server 
		- the state can the the entire stuff in the memory of the primary server 
	- replicated state machine 
		- the assumption is that most services that we want to replicate have some internal operation that is deterministic except when external inputs come in 
		- without external input a computer performs a single instruction at a time and produced deterministic results 
		- only when external input comes in, we cannot assume determinism 
		- they do not send state information between replicas but just the external inputs that arrived in the replica such that we can compare all the external inputs and the order in which they arrive at check if both the replicas have the same request arriving at the same order 
		- some operations internal to the servers are not going to be deterministic between the servers e.g getting the current time between the primary and the backup is going to be different. This is why extra information must be given to the backup by the primary to keep things in sync

- basic FT design of VMware
	- two vmware running in the same local network 
	- vm manager or hypervisior running in both machine in bare metal 
	- hypervisior controls the execution flow inside the vm as well as outside 
	- logging channel for the primary hypervisior to send log data to the backup vm hypervisior
	- shared network disk between the primary and the backup vm hypervisior

- when input arrives from a client then it is directed to the primary hypervisior 
- the hypervisior sends the request both to the guest OS running virtually inside the computer as well as the backup hypervisior
- the backup hypervisior also sends the request to its guest OS 
- if there is a response to be generated only the primary hypervisior is allowed to send response back to the client not the backup
- deterministic replay : record execution primary vm and ensure that the backup runs identically 

- failure detection can be achieved by sending heartbeat messages for by active monitoring the logging channel between the primary and the backup VM 


- operations internal to the VM are deterministic 
- operations external to the VM are non-deterministic 
	- examples of external non-deterministic operations include
		- network packets alongside the interrupt that it generates 
		- weird instructions 
		- multicore instructions
	- when the external client sends a network packet then both the primary and the secondary but be interrupted at the exact same time for them to be in sync 
	- for weird instructions such as current time or day or random number generation, the backup can fake executing the instruction and read the data from the primary 
	- VM-FT ignores multicore VMs i.e the VMs are ran as a single core machine which completely removes the problem that can be caused by multicore instructions

- what kinds of log entries are send in the logging channel between the primary and backup VMs 
	- instruction number inside the machine booted up
	- type of the instruction
	- data that needs to be sent between the servers (this depends on the type of the instruction)

- how is interrupting both the primary and backup at the same time happen
	- both the primary and the backup server has a hardware timer 
	- in the primary when the timer ticks and delivers a interrupt to the VM hypervisor 
	- once the Vm hypervisor is interrupted then it stops the execution of the guest OS and writes down the current instruction of the guest OS
	- it also emulates a hardware interrupt at the guest OS level for the guest OS to keep track of time and perform scheduling operations
	- the instruction no alongside other log entires are send over the logging channel and to the backup server for the backup server to interrupt its guest OS at the same instruction level and time

- what if the backup server's instruction no is greater than the primary's i.e the backup VM is ahead of the primary 
	- the VM hypervisor keeps a buffer that keeps track of the instructions that the primary sends 
	- the VM hypervisor will not execute other instruction until there is at least one instruction in the buffer 

- how to deal with network packets 
	- traditionally when packet arrived at the NIC of the computer then it was DMAed directed into the memory of the computer
		- this means that the computer observed the packets as they arrived in the NIC 
		- this approach is flawed in our fault tolerant VM model because this will keep the primary and backup out of sync 
		- this is because we do not know when the NIC will copy the data into the memory for the OS to obtain the data 
	- so instead 
		- the VM hypervisor will buffer the packet into its private memory region
		- when the NIC interrupts the hypervisor then the hypervisor will suspend operations in the guest OS 
		- writes the instruction no and other log entires to be sent into the logging channel 
		- copy the entire packet into the guest OS's memory region 
		- and the interrupt and NIC interrupt to the guest OS 

- output problems in VM-ft 
	- there are cases where the primary sends response for an operation back to the client which may not have bene performed at the backup server
	- suppose the primary fails after sending back the response then the backup is chosen as the new primary server
	- if this happens then the client gets two different results (one from the updated response of the first primary and another from the backup server because it never gets the new operations to perform from the primary) 
- solution is to use output rule
	- this rule specifies that the primary will not be allowed to send response back to the client until the backup has returned an acknowledgement to the primary telling that it has received all the operations that has to be performed 
	- when a request comes to the primary then it immediately suspends the guest OS and writes the current instruction # in its entry log and sends the entry log to the backup 
	- this needs to happen before the primary generates response 
	- once the response has been generated then the primary waits for the ack from the backup
	- in the backup the log entry is read by the backup's hypervisor and interrupts its guest OS based on the instruction no send by the primary 