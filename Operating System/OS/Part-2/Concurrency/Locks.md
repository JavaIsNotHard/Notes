Locks are variables that are either set or unset during a thread execution, if the lock is set then that means another thread is executing the critical section and if the locks is unset then we thread has to wait until the previous thread unsets the locks for the next thread to acquire the lock.
There are 3 conditions of a locks:
1. Mutual exclusion
2. Fairness of threads
3. Performance of the CPU

A simple thread is something called a spin wait lock which locks the thread when entering a critical section and then unlocks when returning from the critical section. The problem with this lock is during a interrupt, two or more threads can run the critical section at a time which neglects the mutual exclusion case of the lock. 
Another type of thread is the swap and compare thread which is an atomic operation making sure that during timer interrupt another thread cannot enter the critical section. This is done by atomically setting the lock and then returning the previous lock value. This maintains mutual exclusion both does not provide fairness and good performance of the CPU i.e the thread that has to wait will wait until the previous releases the lock.