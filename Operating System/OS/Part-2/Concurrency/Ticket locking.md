fetch and add instruction in most modern hardware to perform this locking where we having a ticket which is kind of a turn variable for local threads and a global turn variable which is global to all the threads. 
```c
typedef struct __lock_t {
	int ticket;
	int turn;
} lock_t;
```

```c
int fetch_and_add(int* addr) {
	int old = *addr;
	*addr = *addr + 1;
	return old;
}
```

```c
void lock(lock_t* lock) {
	int myturn = fetch_and_add(&lock->ticket)
	while (lock->turn != myturn) 
		; // spin wait
}
```
