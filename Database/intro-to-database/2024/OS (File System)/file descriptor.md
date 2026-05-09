an integer number returned by the `open()` system call used to identify the file object that is stored in memory

this integer is private per process i.e we can have a fd of same number in a different process

when we call the `open()` system call the OS does most of the heavy lifting to create the file object in memory 
once the file object has been created a integer number is returned back to the user

we use this integer number to read, write to the file

3 fds exists by default in each process
1. fd 0 -> stdin
2. fd 1 -> stdout
3. fd 2 -> stderr

what the OS does to return the file descriptor number?

- **Validates the path** — checks that the file actually exists on disk
- **Checks permissions** — verifies the calling process has the right to open it
- **Creates a file object in the kernel** which tracks the following:
	- current offset/position of the file
	- access mode 
	- a pointer to the inode (the actual on disk metadata of the file)
- **Allocates a slot in the process's file descriptor table** — finds the lowest available integer (e.g. `3`) and maps it to that kernel file object