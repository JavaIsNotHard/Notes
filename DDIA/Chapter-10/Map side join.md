- the join that we just did with [[sort merge join]] is called reduce side join
- this is because the mapper is not the one performing the join, all that the mapper does is extracts key value pair from the input, assign the key value pair to one of the reducer partition and sort them by key 
- mapper can prepare data that is ready for joining
- the action of sorting, copying to reducer and merging the reducer inputs can be expensive because it depends on the memory buffer that is available and it may write data several times to disk as it passes through various MapReduce stages

-  [[broadcast hash join]]
- [[partitioned hash joins]]
- [[map side merge joins]]


## MapReduce workflow with map-side join
- when another MapReduce job consumed the output from the previous MapReduce job, then the choice of whether map-side join or reduce-side join is used affects the output structure
- if reduce-side join is used then the output is partitioned and sorted by the join key
- if map-side join is used then the output is partitioned and sorted in the same way as the large input because we scan the large input and compare the hash with the in memory hash table 
- map-side join requires the knowledge of size, sort key and partition of the input
- knowing the physical layout of dataset in the distributed filesystem is important for optimization of the join
- 