Running on the CPU introduces a problem. What if the process whats to perform some kind of restricted operation such as requesting an I/O operation or gaining access to more system resources such as CPU and memory?

To solve this problem by introducing two new process mode called the [[user mode]] and [[kernel mode]].

When moving from user mode to kernel mode how can we restrict the process from executing arbitrary code from the kernel? Or better, how does the [[trap]] instruction know which code to run in the kernel mode?
This is done by initializing the [[trap table]] during boot time.
The OS informs the hardware about the location of the [[trap handler]] using some kind of special instructions 

There are 2 phases in the LDE (limited direct execution) protocol. The first phase is when before the execution of the program.