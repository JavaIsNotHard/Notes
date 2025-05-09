Hadoop is somewhat like a distributed version of Unix, where HDFS is the filesystem and MapReduce is a quirky implementation of a Unix process such as sort or uniq

when MapReduce paper was introduced there already was massively parallel processing databases. the biggest difference between the MPP database and MapReduce is that MPP database focus on parallel execution of analytic SQL queries on a cluster of machines, while the combination of MapReduce and HDFS provides something much more like a general-purpose OS that can run arbitrary program

### Diversity of storage

database requires data to be structured according to a particular model where as files in a distributed filesystem are just byte sequences which can be written using any data model and encoding

### Designing for frequent faults

handling of faults and use of memory and disk 
batch systems are less sensitive to faults than online system because they do not immediately affect users if they fail and they can always be run again
fault tolerance in MapReduce is that MapReduce can tolerate the failure of a map or reduce task without it affecting the job as a whole by retrying work, it only retries the failed task
it also writes data to disk frequently (by both mapper and the reducer) partly for fault tolerance and partly on the assumption that they dataset would be too big to fit in memory

if we were running the large job in a MPP database then it would retry the entire query again, this is slow and expensive for large jobs because all the work done previously are lost
instead, MapReduce would be a better approach because retries work at the granularity of an individual task

how realistic are the assumptions that says
1. frequent task failures will happen
2. datasets are too big to fit in memory
3. shared clusters are overcommitted which means tasks are in high risk of being preempted
for Google, these assumptions are true because they have a mixed-use datacenter where both the online production service and offline batch jobs run on the same machine
every task is allocated a resource that is enforced using containers
every task has a priority and the task with low priority are in risk of termination or preemption when the higher priority task arrives
this architecture allows low-priority computing resource to be overcommitted (meaning allocating more resource than needed)
this is ok because when a higher-priority job comes then we can reclaim the resource by terminating the lower-priority job and since MapReduce job at Google are of lower-priority, they are vulnerable to being preempted a lot of time which is why MapReduce is designed to tolerate frequent unexpected task termination