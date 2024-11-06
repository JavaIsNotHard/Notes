- As we discussed in [[Unit-2.1 (Virtualizing the CPU)]] how the OS create many virtual resources out of a single physical CPU, the same thing is applied to virtualizing the physical memory of the computer.
- Suppose a example program similar to [[Unit-2.1 (Virtualizing the CPU)]]:
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char* argv[]) {
	int* ptr = malloc(sizeof(int));
	assert(ptr != NULL);
	printf("(%d) memory address of ptr: %08x\n", getpid(), (unsigned)p);
	*p = 0;
	while (1) {
		Spin(1);
		*p = *p + 1;
		printf("(%d) p: %d\n", getpid(), *p);
	}
	return 0;
}
```
- In the above program, we allocate a 4 byte memory, print the process id of the process. Each process has its own PID. Assign the newly allocated memory with the value 0. Then it calls the Spin function, increments the value and prints the value along with the PID. 
- The output of a single program is not that interesting but when multiple instance of the same program is ran then we see some interesting things. 
- When running multiple instances, the memory for the variable ptr is allocated in the same memory location for different programs. How is this even possible?
- This is possible because each process accesses its own private **virtual address space** which means that each process has its own private space of memory that it can utilize without any additional memory management. Every data that needs to be allocated are allocated in this private virtual space. As far as the process is concerned, it has all the physical memory to itself
- Now this virtual address space is nothing but an illusion that the OS produces. A single physical memory is divided into various virtual spaces for each running program.
- Memory reference within one program does not affect the address space of another program. This means that when we reference the value of memory location 0x2000 from one program it references from its own address space without affecting the address space of another program which in turn can have another value stored at location 0x2000 in its own virtual address space.