A system call is a special type of instruction that allows the user mode to gain access of its various restricted operations. It allows kernel mode to expose certain key functionality to program running on [[user mode]]
To execute a system call, a program must execute a [[trap]]. 

One thing to note is that, it is not the program that jumps to kernel mode. The program is interrupted immediately after it triggers the [[trap]]