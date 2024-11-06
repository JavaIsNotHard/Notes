# Indexes for performance

## Full table scan -> very low performing type of query
This happens when postgres has to scan many different rows and tables in the memory to find the desirable output or result. We know that the heap file contains various block in which various records or rows are stored right? Now those records are stored in the computer's physical secondary memory (SSD or HDD). So postgres has to first load the records from the block onto the physical memory (not secondary memory but primary memory) and then perform the needed operation. 
For example, the query `SELECT * FROM users WHERE username=<someone>` will do a FTS (Full table scan) because it has to load all the records of the table users and then search through those records one by one until it matches the condition `username=<someone>`

## Solutions to avoid full table scan -> Index
takes a column to extract data from or to make an index of -> sorts the index in meaningful way -> places the index in a binary search tree -> the binary search tree will have the root node with certain condition and its children -> if the condition matches then go to that particular child node 
This process makes the scanning for the desired output faster because we neglate other nodes which do not match certain condition specified.

### Creating an index 
`CREATE INDEX ON <table name>(column which we can to index out)`

### Dropping an Index
`DROP INDEX IF EXISTS <name of index>`
the if exists will prevent postgres from throwing error when the specified index is not present
`DROP INDEX <name of index>`
this query will throw out an error when the specified index is not present

## Benchmarking index vs no index
`EXPLAIN ANALYZE SELECT username FROM users WHERE username='something';`

## To view the size of the index and the size of the table 
`SELECT pg_size_pretty(pg_relation_size('users'))` -> to show the size of the users table
`SELECT pg_size_pretty(pg_relation_size('users_username_idx'))` -> to show the size of the `users_username_idx` index

## Downside of index
- takes physical space to store the bst
- slows down insert/update/delete because they have to placed into each rows in the index 
- does guarantee the index will be used 

## Types of Indexes
There are various types of indexes but the most used one is the binary tree index

Columns with types primary key and unique has a index associated with it
