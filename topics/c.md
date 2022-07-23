# Advanced C programming

## Pointers

**What** **are** **pointers**?

Generally pointers are referened to as either pointing to the memory address of a certain value in the computer's memory or pointing to the value itself. A memory address is the placeholder for the value that the user may input. 

```c
#include <stdio.h>
int main()
{
    int num = 100;
    int *numPtr;
    int *num2Ptr;
    int num2;
    numPtr = &num;
    num2 = *numPtr;
    num2Ptr = &num2;
    printf("The value of num is %d, The address of num is %d\n", num, numPtr);
    printf("The value of num2 is %d, The address of num2 is %d\n", num2,num2Ptr);
}
```
