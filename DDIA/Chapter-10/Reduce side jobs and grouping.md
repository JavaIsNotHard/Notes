- joins are necessary when we have to access records on both sides of an [[association]]
- when we want to access record that holds the reference and the record being referenced

- if a query involves join then database needs to use multiple index lookups to get the required value 
- but MapReduce does not have the concept of index 
- rather when MapReduce is given a file then it performs a full table scan which scans a table from start to end
- this is expensive if we are searching for small no of data item 
- but this is a common approach when we are performing analytical queries. this is even better if we can parallelize processing across multiple machines

- number of joins can be reduced by denormalization but cannot be completely removed

- join are very common in OLAP systems 
- the mostly used schema for these type of systems are [[Stars and Snowflakes]]
![[Screenshot 2024-12-12 at 12.54.02 PM.png]]
- let there be two schemas, user activity events which registers all the user events that took place. this is the fact table of the schema
-  another schema is the user database which contains all the user information 
- the activity events schema contains a USER_ID as a reference to the user database

- a simple implementation of join in this type of dataset would iterative through all the user activity events one by one and query the users' database for every userID it encounters 
- this method would suffer from a very poor performance 

- one way to make the above process perform better would be do bring both the events table and the users' table into a single machine 
- then we could have the users' file and the events' file as two inputs for the MapReduce to bring relevant information from both the files and process them effectively

[[sort merge join]]