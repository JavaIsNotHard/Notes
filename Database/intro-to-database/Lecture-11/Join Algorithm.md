Why do we need join algorithms?
if we have multiple normalized tables then we have to perform joins to get combined data between multiple tables using a common column 

the join operation must be done precisely so that it does not have any information loss 

the lecture discusses binary joins mainly inner equijoin algorithm 
here inner means means we only select matching tuples and equijoin means we are only performing an equal operator in the join condition

in general we want our left table or our outer table to to be a smaller table in a binary join where there are two tables in the query plan 


Things to consider in join algorithms
1. what is the output of the join algorithm
	the final output of the algorithm depends on whether we are using:
	- early materialisation
	- late materialisation
2. what is the cost of the join algorithm
	for now we only consider the cost of the algorithm to be the I/O cost required to read and write data back and forth from the disk and to the disk i.e the disk seek and rotation for magnetic disk and data transfer speed. we do not consider other factors such as network cost or time to perform the computation because they are the same for all the algorithms used

the join algorithms are divided into 3 categories 
1. nested loop join
2. sort-merge join
3. hash join

