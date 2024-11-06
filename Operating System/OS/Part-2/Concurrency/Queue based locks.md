Solaris uses a different approach to lock which is by placing the incoming threads into a queue when the flag is not set. 
```c
typedef struct __lock_t {
	int gurad; 
	int flag;
	queue_t *queue;
}
```
The guard variable is used to protect the flag variable and the queue i.e before the value of flag is compared, the value of guard is used and set atomically using the fetch and add instruction. 
This guard variable makes thread spin wait if there is a premature timeout or interrupt right after we set the guard. This allows only one thread to compare its value of flag. 
If the value of flag is 0 then, we set the flag, unset the guard and enter the critical section 
If the value of the flag is 1 then we place the thread inside the lock queue, unset the value of guard to let other thread enter the queue or to enter the critical section and then call park() subroutine. The park and unpark subroutine changes the state of the process of thread from runnable to blocked, the unpark subroutine changes the state from blocked to runnable.
When we release the lock then the following thing happens.
1. If the guard is set then spin wait
2. If there are not other threads in the queue and unset the flag to 0 and unset the guard to 0
3. If there are other threads waiting in the queue then unpark the thread i.e wake up the thread and unset the guard to 0