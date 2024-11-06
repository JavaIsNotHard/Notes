### The Stored Program Concept
The idea that instructions and data of many types can be stored in memory as numbers

Every computer must be able to perform arithmetic operation. For example the MIPS assembly language would add numbers like the following 
```mips
add a, b, c
```
This instruction would add the value of b and c and store the result in a. Each MIPS arithmetic instruction performs only one operation and must have exactly three variables.

When we want to add the value of 4 variables then we are restricted to only using 2 variables so the instruction to add 4 variables would look something like:
```mips
add a, b, c
add a, a, d
add a, a, e
```
Requiring every instruction to have 3 operands conforms the philosophy of keeping the hardware simple: Hardware for a variable number of operands are more sophisticated. 

Only one operation is performed per MIPS instruction

The number of operands are restricted, they must be from a special location called the registers. 
