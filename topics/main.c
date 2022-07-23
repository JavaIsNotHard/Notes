#include <stdio.h>
int main() {
  int num = 100;
  int *numPtr;
  int *num2Ptr;
  int num2;
  numPtr = &num;
  num2 = *numPtr;
  num2Ptr = &num2;
  printf("The value of num is %d, The address of num is %d\n", num, numPtr);
  printf("The value of num2 is %d, The address of num2 is %d\n %d", num2,
         num2Ptr, &num2);
}
