SQL -> parse tree -> relational algebra -> optimized -> execution plan 


query plan is a high level overview of how the SQL query is translated into relational algebra 
the query plan tells what to do but not how to do that, for example the query plan tells to perform a select or a project or a join but not the algorithms to actually perform those operations

there are certain limitations on the algorithms that we can use for our queries, one of the main limitation is that the data we are working with will typically not fit entirely in memory hence needs to be spilled to disk or the algorithms have to work with data that directly reside on disk. 
Also we cannot assume that the intermediate result between the also cannot find entirely in memory

Hence the design of the algorithm or the choice of the algorithm must be such that it can effectively read and write from and to disk 

Data on disk unless they are clustered based on the index are unsorted by default because most database uses a heap storage layout that stores data where ever there is free space available and if we want the physical layout of the data to be sorted by default then we need to use a clustered index which follows the ordering of a B+ tree

when when performing an query operation we need to sort the data first

External merge sort algorithm is the one that is used to sort the data
why do we need to sort?

- we could have a clustered index for one column but need to sort column 
- operations like ORDER BY explicitly asks for sorted data hence if the data is already sorted then we can focus on other optimizations
- we could also remove duplicate results from the row if they are sorted and these are used the DISTINCT command 
- building the index from bottom up rather than top down if we already have a sorted leaf node
- they are also helpful in GROUP BY operation because we can linearly scan all the values until we reach the next value 

the algebra expression can be annotated with the algorithm to be used for a specific operation or a particular index or indices to use and so on. a relation algebra annotated with an instruction on how to evaluate it is called an evaluation primitive. A sequence of evaluation primitives that is used to evaluate a query is called a query-execution plan

most of the database that supports out of memory sorting uses the external merge sort 

