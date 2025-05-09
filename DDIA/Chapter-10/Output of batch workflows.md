batch processing is basically analyzing a large volume of data in period of time
the output of batch workflow is not analytics or report but rather some other kind of structure such as 
1. search index that is build using a large dataset of URLs 

basically in batch processing, we scan a large dataset  and run data transformation which outputs the large dataset into other structure such as files, or index files, or tables and so on based on the requirement of the business as well as the output is structured such that it can be input to another process

2. another example is a key-value store as a batch process output: the output of those batch jobs is often some kind of database that can be queried by the user. the database is going to be separate from Hadoop infrastructure so how are we going to write the output of the Hadoop system into the database? we can use the client library provided by the database such as JDBC and ODBC and use them directly in the mapper and reducer workers and instruct them to write directly to the database through the client. what are the downsides of this approach?
	1. the network request for every single record is slower than the normal throughput of a batch task
	2. if multiple mappers or reducers write to the same database at the same time then the rate may exceed the database connection and overwhelm the database
	3. 

a better approach would be to build a brand new database inside the batch job and write it as files to the job's output directly in the filesystem. the files are immutable once written and are later loaded in bulk into the server that handles read-only queries. here there are no side effects that could be caused due to external dependencies