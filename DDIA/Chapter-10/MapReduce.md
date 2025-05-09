- the unix pipeline where ouptput from one program is redirected as input to another program such that we can create useful program 
- mapreduce is like a unix tools but instead of using local computation, we distribute the computation to various computer 

- the mapreduce job does not modify the input and does not have any side effects other than producing output
- MapReduce reads and write file from and to a distributed file system 
- Hadoop's implementation of MapReduce uses the HDFS (hadoop distributed file system ) as its primary primary file system which is an implementation of GFS

- HDFS works in [[share nothing architecture]] instead of shared disk architecture in [[network attached storage]] or [[storage area network ]] 
- HDFS has a daemon process running in each node that runs a service that allows other nodes to read and write into the file system 
- a central server called NameNode keeps track of which blocks of files are located where
- HDFS gives an illusion of big filesystem by using all the share nothing nodes and using all the space available in those node's disk 

[[MapReduce job execution]]

[[Reduce side joins and grouping]]

