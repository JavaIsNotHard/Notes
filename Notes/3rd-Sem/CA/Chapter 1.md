# 1.1 Information are bits + context

# 1.2 Programs are translated by other programs into different forms 

# 1.4 Processors reads and interprets instructions stored in the memory 

## 1.4.1 Hardware organization of a system 
## 1.4.2 Running the `hello` program 

# 1.5 Caches matter 

# 1.6 Storage devices form a hierarchy

# 1.7 The operating system manages the hardware 

![[operating-system.png]]

## 1.7.1 Processes
When we run a simple program as such as a `hello` program in a modern computer, we get a illusion that the `hello` program is the only program that is actively running in the computer and all the computer's resources such as main memory, processor and the I/O device are being used by only a single program. This is due to the existence of something called **process**. 

Even though there are 100s of processes that are being ran at a time in a single computer it doesn't feel like that. This is because of **context switching** which switches among various processes.

Let us assume that we have a uniprocessor system which can only execute one process at a time. The operating system keeps track of the context of a process which includes all the information necessary for the process to run such as the value of the program counter, the values of the registers and many more. When the operating system needs to transfer the control of the current process to a new process, it first needs to save the context of the current process and load the context of the next process pass control to the new process. 

![[context-switching.png]]

The above figure is an example of how context switching works. First there is a single process running in the processor, suppose we have to read from a file, then the application first invokes a special function called as a system call which passes the control over to the OS or the OS kernel. The kernel performs the read operation and returns the control back to the first process. 
**NOTE**: The kernel manages all the system processes and is not a separate process. 

## 1.7.2 Threads

## 1.9.1 Amdahl's law 
This law gave us how effective is it to improve the performance of a single part of the system and how improving a single part of a system affects the overall performance of the system. 
Suppose executing a application takes $T_{old}$ times and a part of the computer system takes fraction $\alpha$ of the this time and we improve its performance by a factor of $k$ then Amdahl's law helps us compute the speedup time as 
	$$ 
	S = \frac{1}{(1-\alpha)+\frac{\alpha}{k}}\ $$
So suppose we have a part which consumes 60% of the total time executing a application ($\alpha$ = 0.6) and is sped up by a factor of 3 ($k$ = 3) then we can calculate the speedup time as 
	$$
	S = \frac{1}{(1-0.6)+\frac{0.6}{3}} = 1.67
	$$
which means that even though we speed up the part by a factor of 3 we still we only able to improve the overall performance of the system by (x1.67).

## 1.9.2 Concurrency and Parallelism
***Concurrency*** can be referred to as a system with multiple, simultaneous activities and ***Parallelism*** can be referred to as the use of ***concurrency*** to make the system run faster. 
