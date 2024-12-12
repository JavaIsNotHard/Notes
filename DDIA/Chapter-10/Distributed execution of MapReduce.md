- one difference between unix tools and mapreduce is that, MapReduce can compute in parallel without having to explicitly handle the parallelism like we have to in unix tools 
- the mapper and the reducer do not know where the input is coming from and where the output is going to 
- this makes it possible to redirect input from a different node and output to a different node in parallel

- the [[mapper]] and [[reducer]] can be unix tools but mostly they are implemented using conventional programming languages such as Java 
![[Screenshot 2024-12-12 at 11.19.07 AM.png]]
- the above diagram shows the data flow for Hadoop MapReduce job 
- the job is parallelized into m different tasks from m1, m2 ... mn
- the input for each map task is an HDFS directory
- each file or file block is considered to be a separate partition that can be processed by a map task 
- the MapReduce scheduler tries to run a mapper that locally has the file it is told to process i.e the scheduler tries to run the mapper on one of the machines that stores a replica of the input file
- this principle is known is putting the computation near the data and this reduces a network round trip time and increases locality

- the MapReduce framework needs to make sure the application code i.e the [[mapper]] and [[reducer]] are copied and ran in the appropriate machine before the input is fed.
- for mapper the files and file blocks are the partition boundaries, the reduce side of the computation is also partitioned 
- the no of mapper can be different from the no of reducer, the no of mapper depends on the input but the no of reducer can be configured by the user
- the framework also needs to make sure that key-value pair with the same key are computed in the same partition. this is done by calculating the hash of the key 

- the key-value pair that the mapper produces must be sorted 
- but if we are working with terabytes to petabytes of data, traditional sorting algorithm are going to fall behind
- instead sorting similar to [[LSM-Tree]] and [[SSTables]] are used 
- each map task partitions its output or creates new file as output based on the reducer using the hash of the key 
- the partition or the files are then written to a sorted file  on the mapper's local disk 

- whenever the mapper extracts the key-value pair from the input and writes the sorted output to its local file, then the MapReducer scheduler notifies the reducer that they can start fetching the output files from the mapper 
- then then reducer connects to the mapper and downloads the files of sorted key-value pairs for their partition. This means that, reducer only copies or downloads file that scheduler's partition algorithm assigned it with
- the reducer merges files with the same key preserving the sort order
- the reducer scans over the merged files with the same key and generate output that is written to the distributed file system 