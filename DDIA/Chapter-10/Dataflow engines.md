the problems of MapReduce are fixed using execution engines for distributed batch computation which includes Spark, Tez and Flink

they all have one thing in common: they handle an entire workflow as a single job rather than breaking down the flow into multiple subjobs such as different MapReduce jobs chained together. we have already discussed the problem with such approach

dataflow engines work by repeatedly calling a user-defined function to process one record at a time on a single thread 
they parallelize work by partitioning inputs and they copy the output of one function over the network to become input to another function
