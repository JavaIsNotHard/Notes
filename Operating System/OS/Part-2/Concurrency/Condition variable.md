Condition variables are explicit queues on which threads but themselves on when the current execution state is not desirable.

Conditional variable are used to make sure the a running thread waits for another thread to completed before it runs again. The wait is done on the basis of a certain condition defined. Each condition variable has a lock associated with it.

// understand why there is a lock associated with each condition variables

A condition variable is defined using `pthread_cond_t c` and can be passed to `wait()` and `signal()` routines. The `wait()` routine atomically puts the calling thread to sleep and releases its lock. The condition is defined inside the some routine which calls the `wait()` routine. When returning from `wait()` routine, it tries to reacquire its previous lock.

The `signal()` routine is used to wakeup a sleeping thread.

A condition variable has a state variable associated with it which determines the state of the program. The condition that a program wakes up from sleep could be the completion of a function execution, when exiting the function we could update the state variable such that it wakes up the parent thread.

## The fork/join problem
how to make sure that a parent thread waits until a child thread is executed before running the parent thread again

how to implement pthread_join() such that a child process is execute first when created before the next parent instructions are execute in sequence.

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thread_exit() {
	pthread_mutex_lock(&m);
	done = 1;
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);
}

void *child() {
	print("child\n");
	thread_exit();
	return NULL;
}

void thread_join() {
	pthread_mutex_lock(&m);
	while (done == 0)
		pthread_cond_wait(&c, &m);
	pthread_mutex_unlock(&m);
}
```

The basic requirements to use the condition variable properly includes:
- State variable -> These are very important when using condition variables because they tell whether the current state of the program has changed or not. Wait was used to go to sleep because the current state of the program was not desired, but if we were to not use a state variable then the calling thread would sleep forever 

```c
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thread_exit() {
	pthread_mutex_lock(&m);
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);
}

void *child() {
	print("child\n");
	thread_exit();
	return NULL;
}

void thread_join() {
	pthread_mutex_lock(&m);
	pthread_cond_wait(&c, &m);
	pthread_mutex_unlock(&m);
}
```

- Locks -> The wait routine requires both the condition variable and a mutex as argument. Suppose before the wait routine was called a timer interrupt occurred and switched to thread 2 or child thread. This thread on exit would set done and then wakeup a thread from the condition variable. Since there are no threads in the condition variable, so it returns nothing. Now that the parent thread is given execution again and it calls the wait routine, in this case the main thread is going to sleep forever because it had already previous checked the state variable done. This all happened because lock was absent and due to timer interrupt, some other thread was able to produce race condition. **Therefore locks are very necessary when calling the wait routine but not so much when calling the signal routine.** 

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thread_exit() {
	done = 1;
	pthread_cond_signal(&c);
}

void *child() {
	print("child\n");
	thread_exit();
	return NULL;
}

void thread_join() {
	if (done == 0)
		pthread_cond_wait(&c, &m);
}
```

### Producer/Consumer Problem
Also known as the bounded buffer problem where there is a producer which produces some values into a buffer and a consumer which consumes value from the buffer. 
```c
int buffer;
int count = 0;

int get() {
	assert(count == 1);
	count = 0; 
	return buffer;
}

int put(int value) {
	assert(count == 0);
	count = 1;
	buffer = value;
}

void *producer(void *args) {
	int loops = (int) args;
	for (i = 0; i < loops; i++)
		puts(i);
}

void *consumer(void *arg){
	while (1) {
		int tmp = get();
		printf("%d\n", tmp);
	}
}

// A simple producer consumer program
```
Here, the value of buffer is a shared resource so we must synchronize the values to avoid race conditions. We can do this using condition variables. 
```c
int loops
cond_t c;
mutex_t m;

void *producer(void *args) {
	for (int i = 0; i < loops; i++) {
		pthread_mutex_lock(&m);
		if (count == 1)
			pthread_mutex_wait(&c, &m);
		puts(i);
		pthread_mutex_signal(&c);
		pthread_mutex_unlock(&m);
	}
}

void *consumer(void *args) {
	for (int i = 0; i< loops; i++) {
		pthread_mutex_lock(&m);
		if (count == 0)
			pthread_mutex_wait(&c, &m);
		int tmp = get();
		pthread_mutex_signal(&c);
		pthread_mutex_unlock(&m);
		printf("%d\n", tmp);
	}
}
```
The above code uses locks, state variable, wait and signal to implement condition variables.
Here we will understand the problem with using the if statement to check the condition to call the wait function.
When we use if statement to check the condition then it only checks once and never rechecks the condition again. Suppose we have two consumer threads and a producer thread. The first consumer thread (c1) tries to consume value from the buffer, but the buffer is empty so puts itself to sleep. Then a producer (p) is ran, it checks the value of count and sees it as 0 (empty buffer) so fills the buffer, changes the state variable count, wakes up (c1) i.e places c1 is ready state and reruns the producer thread. The second execution of the producer thread rechecks the condition, here count = 1 hence it will place itself to sleep. Suppose instead of c1, c2 were to be executed instead, then c2 could consume the value and when it again sleeps and c1 is executed c1 again cannot consume the value because when c2 consumes, it empties the buffer with count = 0 and when c1 tries to consume it, it finds that buffer is empty and hence will fail the assertion.
Suppose in this case we were to use while loop instead of if statement, then the value of count is rechecked before it attempts to consume the value and finds that the value of count = 0 and puts itself back to sleep again, waiting for another thread to wake it up.

**Mesa Semantics**: There is not guarantee which thread will be ran after it has been placed on ready state or it has been woken up. 

The second problem arises when all three threads c1, c2 and p are placed on sleep. This happens when a consumer thread calls another consumer thread. 
```c
cond_t empty, full;
mutex_t m;

void *consumer() {
	for (int i = 0; i < locks; i++) {
		pthread_mutex_lock(&m);
		while (count == 0)
			pthread_condition_wait(&fill, &m);
		put(i);
		pthread_condition_signal(&empty);
		pthread_mutex_unlock(&m);
	}
}

void *producer() {
	for (int i = 0; i < locks; i++) {
		pthread_mutex_lock(&m);
		while (count == 1) 
			pthread_condition_wai(&empty, &m)
		int tmp = get()
		pthread_condition_signal(&fill)
		pthread_mutex_unlock(&m)
		printf("%d\n", tmp)
	}
}
```
