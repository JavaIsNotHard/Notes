Data are arranged in different level from level 0 all the way to n. The data at level 0 represents the data just brought from the in-memory [[Memtable]] after a memory flush.
Data in each level is sorted because of the use of SSTables. In each level, data is partitioned into multiple SSTable files or segments.
Data are stored as balanced trees and we can perform binary search in each level 
All non-zero level have a threshold or target size. Goal is to restrict each level to be below the target size. 
Compaction triggers when number of L0 files reaches a ``level0_file_num_compaction_trigger``, files will merged to level 1
If level 1 exceeds the target size then one of the segments from level 1 is selected and merged with the level below it i.e level 2
This step is performed for all level and the maximum number of compaction that can be done is handled by the `max_background_compactions`
level compaction also uses [[Subcompaction]]