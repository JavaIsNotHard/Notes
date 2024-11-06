The first thing to note while studying concurrency is the fact that concurrency is not parallelism. Now we can study what concurrency is and what parallelism is and understand why they are not the same thing. 

Thread safe data structure refers to those structures where it has a lock inside a critical section of the data structure. Suppose in a linked list, the lock could be when either updating the value of a node or when updating the value of the address pointed next by the node.

To avoid race condition we need locks
