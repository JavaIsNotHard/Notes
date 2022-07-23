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

Here we can see that the value of `&num` and the value of `numPtr` are the same. They both indicate the memory address of the variable num in the program. Similarly the value of `&num2` and `num2Ptr` are the same.

The next thing we can notice is how `int num2 = *numPtr` gives the value of `num`. This phenomenon is called **dereferencing** or **indirection**. A pointer gives us a reference to an address.

So concluding, a `*<name of variable>` is used to initialize a pointer to the variable, example: `int *ptr` indicates that the variable `ptr` is a pointer and it can point to the value or the memory address of any other variable.



**Strings in C language**

In C language the `string` is just a collection or array of various characters. C does not have a dedicated data type that can hold string themselves. 

We declare a string as `char a[] = "some string";` , here the compiler adds a terminating character called null character `\0` at the very last of the array of characters.

```c
char word[] = "Hello World";
printf("the string is %s\n The first character of the string is %c\n The memory address of the whole character array is %d\n And the memory address of the first index of the array is %d\n, %d", word, word[0], &word, &word[0], word);
```

Here are couple of things to keep in mind: 

- The address of an array is the same as the first item as the array

- The name of the array is also the address of the array. So `%d` of `word` is the memory address of the array but when we do `%s` of `word` then we are probably **dereferencing** the value which finally gives us the value of the array `word`.

-  `&word` == `&word[0]` == `word` 
  
  

**Pointers in string**

```c
char str1[] = "Hello World";
char *str2 = "Goodbye";
printf("%d %d %s\n", &str1, str1, str1);
printf("%d %d %s\n", &str2, str2, str2);
```

Here we can declare a string as `str1` or as `str2`. But the differences being that `str1`is an array whereas `str2` is a pointer to the array. So the `str1` stored the address of itself whereas the `str2` stores the address of its value. Again, the `str2` hold the address of the array `"Goodbye"`. The pointer variable `str2` is stored in one address, whereas the array it hold i.e `"Goodbye"` are stored another address. 

**Notes: An array variable is a address but the pointer variable is not**

```c
str2 = str1;
str2 = &str1;
printf("%d", &str2, str2);
```

Here both the above code snippet do the same thing i.e display the replace the value of str2 with the address of str1. In the first line, `str1` is a array and we know that an array is also a address. So doing `str2 = str1` we are essentially getting the address of `str1` and giving it to `str2`.



**Multiple Indirection**




