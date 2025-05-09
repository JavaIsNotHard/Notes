- in this join algorithm,
- we join a large dataset with a small dataset
- the small dataset must be small enough to fit entirely into the main memory
- the word broadcast refers to the fact that the in memory small dataset is visible to all the mapper task which are operating on a small chunk of the large sized input
- the small dataset is read from the distributed filesystem into an in memory hash table 
- then the large input is scanned and the corresponding hash key is hashed to find the corresponding joining record in the data item in in memory hash table


- let us take an example, we have user profile database and a user event database, the user profile database contains small user dataset which can be easily scanned through, on the other hand we have the user event database which is large since it needs to record events that happen periodically over time
- now we need the small dataset to be small enough to fit in the memory of the mapper in the map side and then it needs to create an in-memory hash of the data


## My interpretation of how broadcast hash join works
- when the Map Reduce job initializes then the first thing it does is it loads the small dataset into the memory of all nodes working in the Map Reduce job i.e the same small dataset is loaded into the memory as a hash table in all the worker nodes 
- next the large dataset is partitioned into n chunks depending on the number of worker nodes such that we can assign 1 worker node to 1 partition of the large set to add parallelism
- now for every record of the subset of the large dataset, it looks up the matching key in the local hash table and performs. the join operation
- the word broadcast reflects the fact that each mapper for a partition of the large input reads the entirety of the small input, the small input is effectively broadcasted to all partitions of the large input

- instead of loading the small join input into memory we could store the small join input in a read-only index on the local disk of the worker node 
- the frequently used parts of the index will be cached in the OS page cache, this way we can access lookups almost as fast an in-memory hash table, but without requiring the dataset to fit in memory