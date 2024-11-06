This section constructs an ALU from four hardware building blocks (AND, OR, inverters and mux) and how combinational logic works.
Because the MIPS processors are 32-bit wide, we need to create a 32-bit ALU. To create a 32-bit ALU we need to create 32 1-bit ALU.

## A 1 bit ALU
To implement the functionality of AND and OR we can use an AND gate and an OR gate then we use a MUX to select either the AND or the OR operation. 
To implement the functionality of addition, we need to make an adder. An adder takes in 2 inputs and gives us a output. Since we are builing a 1 bit ALU both the inputs and the output are of a single bit. We also need a second output bit called the CarryOut which indicates whether the last operation had a carry or not. The value fo the CarryOut must be added to the operation of the next bit so we need a third input bit called CarryIn which takes in the CarryOut bit of the previous operation.
Now we can construct the truth table for all the inputs and the outputs as follows:

| A   | B   | CarryIn | CarryOut | Sum |
| --- | --- | ------- | -------- | --- |
| 0   | 0   | 0       | 0        | 0   |
| 0   | 0   | 1       | 0        | 1   |
| 0   | 1   | 0       | 0        | 1   |
| 0   | 1   | 1       | 1        | 0   |
| 1   | 0   | 0       | 0        | 1   |
| 1   | 0   | 1       | 1        | 0   |
| 1   | 1   | 0       | 1        | 0   |
| 1   | 1   | 1       | 1        | 1   | 

Here we can use the canonical form to find the boolean expression for each output. For example, to find the boolean expression for the output CarryOut:
`CarryOut = (b.CarryIn) + (a.CarryIn) + (a.b) + (a.b.CarryIn)`

Now based on the boolean expression we can also construct the gates necessary to implement the CarryOut functionality. Note that since if `(a.b.CarryIn)` is true then all the other expression must also be true, so we can neglect this operation. So the final boolean expression would look something like this:
`CarryOut = (b.CarryIn) + (a.CarryIn) + (a.b)`

To implement this expression using gates we see that it requires 3 AND gates and a single OR gate which sums all the ANDed product.

## A 32 bit ALU
To implement a 32-bit ALU we are going to create 32 individual 1-bit ALU. 

Quizes: 
1. Suppose you want to add the oepration NOT(a AND b), called NAND. How could the ALU change to support it?