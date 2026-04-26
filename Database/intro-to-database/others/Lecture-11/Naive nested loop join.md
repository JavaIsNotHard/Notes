the most computationally expensive join algorithm 
since we are only considering binary tables i.e 2 tables when considering the join algorithm, we make the following assumptions:
1. we have M pages of data for relation R, m tuples inside the relation R
2. we have N pages of data for relation S, n tuples inside the relation S

the algorithm used by naive nested loop join is as follows:
```
for each tuple in R:
	for each tuple in S:
		if r and s match on join condition:
			output(r, s)
```

the cost of the algorithm is as follows:
cost = M + (n * N)
because we bring M pages of relation R into the memory
and for each tuple inside the page that we bring in memory we scan through all the pages N
Algorithmically we can annotate the runtime cost as O(n^2)
this is only if we are considering we have to bring data from disk and we don't have any data cached in memory or the buffer cache of the database engine