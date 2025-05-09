every MapReduce job is independent from every other job 
the contact point between the job with the rest of the world are its input and output directories on the distributed filesystem
the output of one job can be input to another job if both the reducer of the first job and mapper of the second job reads and writes to the same directory, a external scheduler must start the second job only once the first job has completed

in most cases the output of one job is only every used as input to one other job which means that if there are multiple MapReduce jobs then the output of most of these jobs are just intermediate state: means of passing data from one job to the next 

the process of writing out this intermediate state of files is called materialization which means early computing the result of some operation and writing it out rather than computing it on demand when requested

this materialized approach has its own downsides
1. MapReduce job can only start when all tasks in the preceding jobs have completed, whereas processes connected by a unix pipe are started at the same time with output being consumed as soon as it is produced
2. mappers job in the whole chain is redundant to the process because the only job of the mapper is to partition the input data and prepare it for the reducer so we could rather have one mapper and chain reducers directly without having intermediate mapper stages
3. storing intermediate files in distributed file system means that they are likely to be replicate among the replicas which is an overkill for temporary data


[[Dataflow engines]]