- relative path -> path relative to the current directory 
- absolute path -> path absolute to the root directory (/)

## The file system interface
- `open()` system call which creates a file and returns the file descriptor identifier which points to the file's internal OS structure.
- Once we have the file descriptor then we can use methods such as `read()` and `write()` 
- Each process has its own open file descriptor array
```c 
struct proc {
	...
	struct file *ofile[NOFILE];
}
```

- The offset of the current file is kept in the `struct file`
```c
struct file {
	int ref,
	char readable,
	char writeable, 
	struct inode *ip,
	unit off; // offset counter
};
```

- A global open file table keeps track of all open files in the OS
- Each process's file struct points to a single entry in the open file table excluding the case where the child process of a parent also points to the same entry in the open file table.

## Writing immediately with fsync()
- writes to disk are buffered in memory by the OS to provide better sequential writes on disk.
- To prevent this data buffering instead of `write()` method we can use the `fsync()` method which immediately writes to the disk.

## Getting information about files
- the `stat` command line utility as well as the `struct stat` contains information about the files.
```c
struct stat { 
		dev_t st_dev; // ID of device containi
		ino_t st_ino; // inode number 
		mode_t st_mode; // protection 
		nlink_t st_nlink; // number of hard links 
		uid_t st_uid; // user ID of owner 
		gid_t st_gid; // group ID of owner 
		dev_t st_rdev; // device ID (if special file) 
		off_t st_size; // total size, in bytes 
		blksize_t st_blksize; // blocksize for filesystem I/O 
		blkcnt_t st_blocks; // number of blocks allocated 
		time_t st_atime; // time of last access t
		ime_t st_mtime; // time of last modification 
		time_t st_ctime; // time of last status change };
```

- OS keeps this type of information in a structure called inode

## Removing files 
- linux has an `unlink()` syscall instead of `remove` or `delete` methods


## Creating directories
- when a directory is created, it is filled with two entires: one entry that refers to itself and another that refers to its parent.

## Hard links
- when two files points to the same inode number then we create a hard link between them and increment the reference count.
- when we unlink a file then we decrement the reference counter, until the reference count is not zero then the file will not be deleted.\
- we call unlink when we remove file because once we unlink the file it will not reference to any inode meaning it wouldn't have any content of itself.

## Making and mounting a file system
