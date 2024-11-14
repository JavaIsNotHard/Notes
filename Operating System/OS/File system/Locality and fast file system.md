![[Screenshot 2024-11-13 at 14.07.00.png]]

- The old unix file system 
- simple implementation
- had bad performance, only provided 2% of overall disk bandwidth
- Data was spread across the disk without regards to the underlying medium i.e disk 
- Data blocks pointed by the inodes where far away which meant additional disk seek 
- Data would be fragmented, which made a lot of bad and forth access of data on disk which reduced performance. 
- 