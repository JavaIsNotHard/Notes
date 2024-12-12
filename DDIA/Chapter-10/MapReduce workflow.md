- chain of MapReduce jobs that cannot be achieved using a single MapReduce job 
- example could be do find the most popular URLs based on the log 
- a single MapReduce job could could the page views per URL but nothing more 
- a second MapReduce job is needed to take the page views per URL as input and produce the most popular URLs by performing a ascending order sort

- Hadoop MapReduce does not have builtin support for workflows 
- to solve this problem, the first job needs to be configured to write to a particular directory X and the second job needs to be configured to read from the directory X as well

- A batch jobs' output is only considered valid when the job has completed successfully
- Or a job in the workflow can only start when the prior job that produced the input for the current job has completed 
- various workflow schedulers have been developed for Hadoop like AirFlow, Oozie and more 

- workflow involving 50-100 jobs are common when building recommendation systems 
- when different jobs are used for different purposes then different team members can be allocated the operation of a particular job in an organization
- 
