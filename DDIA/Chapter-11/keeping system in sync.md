- [[heterogeneous data system]] contains more than one data storage and retrieval system 
- each system will have their own copy of data and the data will be represented in their own way or in an optimized way for later processing

- this asks for data between these systems to be in sync with each other
- suppose if a user performs a write operation to the database then this changes must be recorded in the cache, search index and even data warehouse for analytics
- this can be done using batch processing where database files are used as input to the mapper and the reducer will perform the action of storing the data to their respective system 

- this requires the database to dump their content from time to time which is an expensive operation
- another approach is to use [[dual writes]]