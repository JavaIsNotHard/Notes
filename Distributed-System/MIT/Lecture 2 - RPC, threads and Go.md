## Why even care about threads? 
Threads are going to be used to manage concurrent in programs. 
Concurrency is very interesting and important in distributed systems. 
In distributed system we will have one program talking to a bunch of other services so we need to allow our program to do so without too much complex programming. This is where threads comes in. 

Threads in Go is called goroutine. They are said to be lighter than threads but the main function of a goroutine is identical to a OS thread. 

## What is a thread? 
We have one program and one address space, in a sequential single threaded system, there will be one thread executing code in that address space, one program counter, one set of resgister and one stack. 
In multi threaded system we will have mutliple threads as the name suggests and this allows for multiple point of execution, multiple stacks and multiple set of private registers. 
Each thread will be executing instructions that are different than other threads. **The main idea of thread is to allow program to be in its own point in a different activity**. 

### Why do we need thread?
- I/O concurrency 
		While one thread is busy writing some stuff back to the disk, we can spin another thread that would do some computation necessary to write back to the disk such that the thread that was previously writing after completion could theoretically immediately write back stuff without having any wait time. 
- CPU parallelism 
		If we can spawn up multiple threads of multiple cores of a multi-core CPU then we could get n times the performance of the CPU.
- Convenience 
		Doing some stuff periodically, suppose firing a goroutine to perform some checks like in a map reduce system, a master thread could check the worker thread if they are working properly every n seconds or minutes. Basically we want to do something without having to manually intervene to perform that thing. 

## How to operate without threads? 
This is where the concept of **asynchronous programming** or **event-driven programming** comes into play. 
This style has a single thread and a single loop 
Waits for any input or event that might trigger the processing like an timer going off, or a arrival of a request of a client. 
single thread of control -> whenever it gets an input -> lookup a table to map what the current state of the client is within that request

Pain to program 
Can get I/O concurrency but cannot get parallelism (because waiting in a single loop for any request)

The overhead of event-driven programming is less than threads 
Why? 
A single thread sits on a stack (a stack is a 1KB to 8KB), if we have some small amount of running threads then no problem, but if we have millions of threads then we have a lot of problem. The scheduler for the thread is going to be complicated and starvation can occur more.

We could also utilize multicore feature by running a single thread in each core and running a loop in each thread such that we have n number of event listeners listening for any events to occur. 

### Challenges with threads 
what to do with shared data?
- race condition
	- how to prevent this?
		- locks
- coordination between threads 
		threads depending upon other threads for further operation. Threads wait for each other. Ways to solve coordination between threads in golang 
			- channels 
			- waitgroup 
			- condition variable
- deadlocks 

### Web crawler 
Examples of using thread practically: 
