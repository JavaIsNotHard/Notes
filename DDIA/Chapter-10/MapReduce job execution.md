- MapReduce is a programming framework that allows us to process large dataset in distributed filesystems like HDFS 
- the workflow is the same as the unix tools that we use which consists of following steps:
	- read input file from the file system and break the file into records 
	- each record is processed by the mapper which extracts key-value pairs from the record
	- the key-value pair is then sorted based on the key
	- the sorted key-value pair is then passed to the reducer for it to iterate over all the key-value pair. multiple occurrence of the key-value pair can be grouped together because they are sorted previously without keeping additional memory overhead.


- step 2 and 4 is where we write our custom data processing logic
- to create a MapReduce job, we need to create two callback functions, [[mapper]] and [[reducer]]

[[Distributed execution of MapReduce]]

[[MapReduce workflow]]
