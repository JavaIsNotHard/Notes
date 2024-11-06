Threads can be viewed as a function that runs on the same memory space as other functions at the same time. A single program can have multiple threads and each thread access the same memory space as of the other functions such as data structures, variables and much more. For example, 
```c
int counter = 0;

void* worker(void* args) {
	int i;
	for (i = 0; i < args; i++) 
		counter++;
	return NULL;
}

int main(int argc, char* argv[]) {
	// define the length of the argv and define thread indentifiers p1 and p2
	pthread_create(&p1, NULL, worker, NULL);
	pthread_create(&p2, NULL, worker, NULL); 
	return 0;
}
```
The program above creates two worker threads in the same program and p1 and p2 are used to as a identifier to them.