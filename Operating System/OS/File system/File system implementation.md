- file system are stored on disk 
- disks are divided into various partitions and each partition has its own independent file system 
- Sector 0 is called the master boot record is used to boot the compter .
- The end of the MBR contains the partition table.
- The table contains the start point and end point of each partition.
- When the computer boots up the BIOS reads from the MBR.
- The MBR itself locates the first active partition which usually is the boot loader partition
![[Screenshot 2024-11-12 at 13.12.04.png]]

## Ways to think about the file system 
The file system is represented by 
- the data structures  of the file system 
- the access methods 


- disks are divided into blocks of some fixed size (normally 4KB in size)
- the region on disk for user data -> data region
- we reserve some fixed block for the data region
- the metadata of the file is stored in the inode which is located in the remaining blocks
- inode typically takes up 128 to 256 bytes of space. If we have space for N inodes then can only create N unique files.
- Another structure required is allocation structure which checks for free space in inode block and data region

- allocation structure contains algorithms such as freelist which points to the first free block which then points to the next free block and so on. 
- Another method is using bitmap, one for the data region and one for the inode region.

- the final block that is remaining is the suuperblock and contains all kinds of information about the file system.
![[Screenshot 2024-11-12 at 13.28.45.png]]

- Each inode has an inode number which helps to find here in the disk the inode exists
- Each inode has either a direct pointer a multiple indrenct pointer. 
- The direct pointer points to the location where the data blocks for the file exists. 
- direct pointers are not good is cases where the file size in bigger than the disk block size multipied by the no of direct pointers because the inode would not be able to hold them.


### Multi level index 
- use of indirect pointers i.e point to a block which contains more pointers, each of which points to the user data.
- many direct pointers and a single indirect pointer
- if the file grows large then another indirect pointer is added 


- directory also have inode numbers as well as list of other directories and files
- each directory contains the following entires: 1. inode number, record length (total bytes for the name plus some left over space), strlen(the actual length of the name).
- file system treat directories as special file i.e they also inode entries in the inode table.
- 

