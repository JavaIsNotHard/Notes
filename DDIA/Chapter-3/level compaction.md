Data are arranged in different level from level 0 all the way to n. The data at level 0 represents the data just brought from the in-memory [[Memtable]] after a memory flush.
Data in each level is sorted because of the use of SSTables. In each level, data is partitioned into multiple SSTable files or segments.
Data are stored as balanced trees and we can perform binary search in each level 
All non-zero level have a threshold or target size. Goal is to restrict each level to be below the target size. 
Compaction triggers when number of L0 files reaches a ``level0_file_num_compaction_trigger``, files will merged to level 1
If level 1 exceeds the target size then one of the segments from level 1 is selected and merged with the level below it i.e level 2
This step is performed for all level and the maximum number of compaction that can be done is handled by the `max_background_compactions`
level compaction also uses [[Subcompaction]]

![[Screenshot 2025-05-06 at 8.59.16 AM.png]]

each level except for level 0 contains multiple SSTable files which are range partitioned based on their key

we can use binary search algorithm to search a level to find which file contains the key we want then we can binary search inside the file to find the key in the file 

each level except for level 0 as a target size

compaction happens when the number of files in level 0 reaches a certain threshold which is the `level0_file_num_compaction_trigger`
all the files of Level 0 are compacted with Level 1

