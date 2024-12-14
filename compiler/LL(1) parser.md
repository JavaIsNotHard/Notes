- needs [[first table]] and [[follow table]] instead of recursive function call 
- first, we need to construct the LL(1) parse table
	- constructs a 2x2 table where the column contains the non-terminal symbols and the rows contains the terminal symbols 
	- Let T denote the table and T[A, a] denote an entry in the table. the value for the entry will be the production which produced the terminal from the non-terminal
	![[Screenshot 2024-12-12 at 7.27.56 PM.png|200]]
	- for the given grammar the following parsing table is constructed 
	![[Screenshot 2024-12-12 at 7.27.22 PM.png|300]]
	- the first and follow table of the grammar is given below
	![[Screenshot 2024-12-12 at 7.23.38 PM.png|500]]
	- the numbers indicate the production rule index number. For example since using the first table we were able to derive that P can derived `int` and P can also derive `(` looking at the first table
	- 
- then we start the LL(1) table parsing algorithm