direction in which data is flowing

- pull based (demand-driven pipeline)
- push based (producer-drive pipeline): 
	- the parent operator are not calling the next() method of its child. they are trying to keep data in CPU caches and also in CPU registers
	- Allows for tighter control of caches / registers in operator pipelines. How?
		- in pull based model or the [[Iterator Model]], we are frequently calling the next method of the child, a method call is basically a JMP instruction in the CPU which means that it has to context switch based on the method we called, and when we context switch are basically removing existing data from the CPU registers and caches and bringing in new data of the next function call. But in push based when the CPU executes the functionality of a child operator it can **process a full batch** of tuples in **tight loops**, staying in the CPU pipeline longer.
	- also allows for operator fusion where we combine two or more operator into a single one such that we don't have to pass data through various operator multiple times
	- in the pull based model, for each pair of adjacent operators, there is a buffer that holds data between them, the child operator pushed data to the buffer whereas the parent operator consumes data from the buffer, so that means the buffer is shared between the operators
