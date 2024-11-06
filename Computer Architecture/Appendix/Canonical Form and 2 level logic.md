**Canonical Form**: A unique algebraic expression for a boolean function can be obtained from its truth table by ORing the combined minterms for which the function is equal to 1.

A minterms is a product(AND) of all n variables in which each variable is complemented if its corresponding value if 0 and not complemented if its corresponding value is 1. For example, we have function F = 0 for the following variable value x = 0, y = 0 and z = 0. Here all the 3 values of the 3 variables are 0 which means we need the complement product of all 3 variables 
i.e minterm = x'y'z'
Similarly we can deduce the minterm for a function F = 1 where its corresponding variable values are x = 0, y = 1 and z = 0. In this case we have a minterm = x'yz.

Now going back to the definition of canonical form we see that we have to or all the combined minterms where the function has the value of 1.

For example, we have a function F = x + yz and this function has a truth table corresponding to it based on the value of 3 variables x, y and z.

| x   | y   | z   | Minterms     | F   | F'  |
| --- | --- | --- | ------------ | --- | --- |
| 0   | 0   | 0   | x$_o$=x'y'z' | 0    | 1   |
| 0   | 0   | 1   | x$_o$=x'y'z  | 0    | 1   |
| 0   | 1   | 0   | x$_o$=x'yz'  | 0    | 1   |
| 0   | 1   | 1   | x$_o$=x'yz   | 1    | 0   |
| 1   | 0   | 0   | x$_o$=xy'z'  | 0    | 1   |
| 1   | 0   | 1   | x$_o$=xy'z   | 1    | 0   |
| 1   | 1   | 0   | x$_o$=xyz'   | 1    | 0   |
| 1   | 1   | 1   | x$_o$=xyz    | 1    | 0   |

The function F = x + yz can also be expressed in terms of sum of its minterms such as 
F(list of varaiables) = F(list of 1-minterms indices)
i.e F(x, y, z) = $\sum (3, 5, 6, 7)$ because only these columns F corresponding to 1
and can be expressed as boolean expression as sum of minterms such as
`F = x'yz + xy'z + xyz' + xyz`
we can use this expression to build a combinational circuit which gives output similar to the one shown in the table. We can also further perform other boolean operation to reduce the number of gates used which has not been discussed in the chapter.
