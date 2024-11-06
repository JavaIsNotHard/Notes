Unbuffered I/O -> each read and write invokes a system call in the kernel 
Sharing of resources among multiple processes involved the concept of atomic operation 

To the kernel all the files are referred to by their file descriptors 
the file descriptor is an non negative integer which is given to a process by when a file is opened or created using the `open` or `creat` system call that is used as an argument for the `read` and `write` system call 

There are 3 default open file descriptor which are  the standard input, standard output and the standard error whose values are 0, 1 and 2 respectively. 

The maximum number of open file in a newer UNIX system ranges upto 63

Negative offset from files are possible so we need to make sure that we compare the value returned by lseek to -1 to make sure that is not the case. 
lseek records the current file offset within the kernel - it does not perform any I/O 
If the file's offset is greater than the size of the file then the next write will extend the file. This is referred to as creating a hole in the file 

The UNIX kernel closes all open file descriptors in a process when the process terminates

The kernel uses three data structures to represent an open file 
- every process has an entry in the process table. The process table contains a table of open file descriptors. The file descriptor contains the file descriptor flags and a pointer to a file table entry 
- a file table for every open file where each entry contains the status for the file such as read, write etc, the current file offset, a pointer to a v-node (UNIX only) or an i-node (linux) table entry 
- The inode structure information is read from the disk when the file is opened. The i-node structure contains info such as the owner of the file, the location of data block on disk of the file, size of the file and more. 

What happens when two independent process access the same file? 
Each open file will have a different open file descriptor number which means that they point to different file table entry. Even though these are different file table entry it points to the same i-node or v-node structure such that changes from either process are recorded correctly on disk when written back.
One reason for the existence of two file table entry so that each process has its own current offset for the file 