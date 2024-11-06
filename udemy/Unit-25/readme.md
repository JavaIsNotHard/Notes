# Advance Query Tuning

## Working definition of "Cost" 
Amount of time taken to execute some part of the query plan. When the query reaches the planner step of execution it has to decide whether to use a index scan or a sequential scan.
When we use the sequential scan then the following steps are applied 
![[sequential-scan.png]]
The step to process each comment will definitely take some CPU usage as will when loading a block into the memory from the hard disk. This CPU time is what is used to calculate the total cost of the operation. 
We will assume that loading blocks from hard disk to memory takes (1 or cost factor*(no of blocks)) and processing each comment takes 1% of loading each block. Which means (0.01 or cost factor *(no of rows)). So in general we can use the formula
` 1*(no of blocks) + 0.01*(no of rows) = total cost `

## Rules when calculating the total cost:
![[cost-calculation.png]]
The variables at the right are the cost_factor and the variables at the left are no of reads. 
- The value of all the cost_factor depends on the value of `seq_page_cost` which defaults to 1.0.
- The value of `random_page_cost` is 1% of the `seq_page_cost` which is 0.01.
- The cost of `cpu_tuple_cost` is also 0.01. 
- The cost of `cpu_index_tuple_cost` is 0.005.
- and finally the cost of `cpu_operator_cost` is 0.0025.


## Why are there two costs in the cost table?
![[cost-of-sequntial-scan.png]]
In the given picture, the cost of the first operation is set to 0.00 or 0 and the cost of operating on all the other rows is set to some calculated values. 
Here the first value indicates the cost to produce the first row and the second value indicates the cost of produce all rows.
In the sequential scan, when the first page processes all the rows it can send that value onto the next step of the planner.
![[Mon Jun 26 01:53:53 PM +0545 2023.png]]
In our case the seq scan passes the result onto the hash join section of the process when the seq scan still has other pages to process.
Now you might ask why is the first value of the seq scan set to 0.00? This is because the data needed for the query is already cached in memory, either in the PostgreSQL buffer cache or the operating system's disk cache. In such cases, the database can read the required data directly from memory without incurring any disk I/O cost. 

There are many cases where postgres will not use indexes when if we have created one. The main use of index would be when we want to extract small columns of data out of a large dataset not when we extract lots of column. 
