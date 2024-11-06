- Single replacement for locks and condition variables. 
- A semaphore is an object with an integer value which can be manipulated using two routines `sem_wait()` and `sem_post()`
- We initialize semaphore using the following function `sem_init(&s, 0, 1);` here the third argument is used to pass the initial value of the semaphore which in this case is 1, the second argument is 0 which indicates that the semaphore is shared between threads in the same process. 
- The `sem_wait()` routine is used to decrement the value of the semaphore and the `sem_post()` routine is used to increment the value of the semaphore, both by one
- The value of the semaphore determines the behavior of the routine `wait()` and `post()`
- the `sem_wait()` 

```c
void sem_init(sem_t *s, int value) {
	s->value = value;
}

void sem_wait(sem_t *s) {
	while (s->value <= 0) 
		sleep()
	s->value--;
}

void sem_post(sem_t *s) {
	s->value++;
	wake_one_waiting_thread()
}
```

## how to avoid race condition or how to implement mutual exclusion in semaphores
To implement mutual exclusion without using either locks and condition variable can be challenging but semaphores have the capability of handling this functionality. 
```c
void *worker(void *args) {
	// what goes here 
	for (i = 0; i < 1e6; i++) 
		counter++
	// what goes here
	return NULL
}
```
If we were to initialize the semaphore with an initial value of 1 then we could probably avoid race condition and achieve mutual exclusion. 
```c
void *worker(void *args) {
	sem_wait(&s)
	for (i = 0; i < 1e6; i++) 
		counter++
	sem_post(&s)
	return NULL
}
```
`sem_wait(&s)` would decrement the value of the semaphore by 1 if the value of semaphore is greater than 0. If there was another thread trying to access the critical section in the same time then it would look at the semaphore value of 0 and place itself to sleep. Once the first thread finishes its execution and calls the `sem_post(&s)` function, it would increment the value of semaphore and wake up any other sleeping threading for execution.

## how to solve the fork/join problem 
how to allow the child thread to execute first before executing the parent thread.

## Reader/Writer lock
- Many reader inside the critical section at once or one writer inside the critical section. 
- If we allow writer inside the critical section then we block all the readers from the critical section and vice versa.
