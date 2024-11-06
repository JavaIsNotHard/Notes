Run the program directly in the processor. This is the **direct execution** part of the mechanism.
When a program needs to be executed, 
- It creates a process entry in the [[process list]].
- Then it allocates needed memory
- Then it loads the program into the memory from disks
- Initializes the stack, heap and I/O file descriptors.
- Locates the `main()` routine of the program and jumps to it.
- Starts the execution of the program in the CPU.
The advantage of this mechanism is its efficiency and speed that it executes the program in. The speed that the program executes in depends on the speed of the CPU and there would be no external factors disturbing the execution of the program.

This mechanism has certain problems to it which includes:
- Making sure that the program doesn't do something that it isn't supposed to.
- How OS stops the process from running such that we swap out the process with another one and achieve [[Time sharing]].

Problems related to **direct execution** of program:
- [[Restricted Operations]]
