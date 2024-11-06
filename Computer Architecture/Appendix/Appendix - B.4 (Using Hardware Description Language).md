HDL characterisitics: 
- Provides abstract description of the hardware to simulate and debug the design.
- Using hardware compilation tools, the description can be compiled into hardware implementation.

**Verilog** is the hadware description language that we are going to be using which is based on C programming language. Characterisitics of **Verilog** includes: 
- Specifies the behavioral and structural definition of a digital computer.
	- The behavioral specificiation describes how a digital system functionally operates. What are the operations that we can perform in a digital system and how all falls under the behavioral specification.
		- The structural specification describes the detailed organization of digital system. Used to describe a system in terms of gates and switchesp
A continuous assignment, which is indicated by the keyword `assign`, acts like a combintaional logic function, the output is continuously assigned the value, and the change in the input value is immediately reflected in the output value. 
Assign statements are a way to write Verilog that generates combinational logic

There is also `always` block which is a construct or a procedural block which specifies how signals and variables should be updated in responose to changes in certain conditions. The statements inside the `always` block are always re-evaluted when changes occur in the senesitive signals.
Inside a `always` block we can use various procedural statements such as blocking (=) and non-blocking (<=) assignments, conditional statements, loops and other procedural constructs.
We have two types of assignment that can be done inside the `always` block: 
- blocking assignement(=) => Similar to the C assignment operator where the right side operation is evaluated and is placed onto the value of the left side. 
- non-blocking assignment (=>) => In this assignment all the right side operations are evaluated and assignments are done simultaneously.
 