- extension to the hash join algorithm like [[broadcast hash join]]
- the mapper first loads the small dataset into a partition based on some key 
- once the smaller data is loaded and the hash key of the join key is found then the mapper will scan over the large dataset and also extract the join key -> perform the hash operation -> and use the output hash and compare it with the in memory hash table
- this approaches makes sure that all the inputs that you want to join are located in the same processing node or partition
- this also has the advantage that it only has to load small amount of data into hash table
- for this algorithm to work, both the large dataset and and the small dataset  must use the same hash key and the same hash function


## My interpretation of how partitioned hash join works
- the basic idea of partitioned hash join is that the data is partitioned in such a way that the join key for both the partition are placed on the same worker node partition
- example, we have two large datasets A and B, we partition both A and B across the cluster based on the hash on the join key (user_id), then all records from both tables with the same (user_id) are in the same partition