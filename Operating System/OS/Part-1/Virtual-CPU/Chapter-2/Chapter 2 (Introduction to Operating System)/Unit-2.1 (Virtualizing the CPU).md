- Suppose we have computer with only one CPU it in. All the fetching, decoding and executing is done in this CPU. Now, let us consider a program: 
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "common.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "insufficient arugments");
		exit(1);
	}
	char* str = argv[1];
	while(1) {
		Spin();
		printf("%s\n", str);
	}
	return 0;
}
```
- All this program does is call the Spin function in every loop. The spin function checks the time and returns after every one second and then prints the argument to the standard output. Now running this program in a single CPU would mean that all the resources of the CPU needs to be utilized for this program to run correctly. 
- But when we run the same program's multiple instances such that each instance prints a different argument then we can see that the output are printed in the same time as though we were running a multiprocessor. Why does this happen?
- It turns out that the OS with the help of the hardware creates an illusion i.e the illusion that the system has a large amount of CPU to utilize and thus allowing multiple programs to run at the same time.
There is also something called as the OS policy which states which program to run first when two programs want to run at the same time.