A program typically resides in the secondary memory unit i.e hard disk drive, solid state drive and so on. To run a program the OS must first load its code and any static data into the memory, into its [[Part-1/Virtual-CPU/Chapter-4/address space]].
Earlier OSes used to load the entire program into the memory before running the process but modern OSes [[lazy load]] the program i.e only load stuffs that are needed and then progressively load them as they are needed.
Once the static data and the code is loaded then before running the process, the OS allocates some memory for the [[run-time stack]] and [[heap]]. 
Other [[IO related stuff]] are also initialized by the OS.

![[Thu Dec  7 07:57:44 PM +0545 2023.png]]