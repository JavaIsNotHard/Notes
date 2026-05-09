fixes the flaws of tuple oriented approach

assumes that we can only append blocks instead of overwriting existing blocks

this makes writes faster because we don't have to search for free space and go through various indirection layer but the disadvantage is that our reads are slower because a read has to search for the data in multiple places going from the memtable to different levels in the SSTable and more


the basic idea of this approach is that instead of changing or overwriting an already existing tuple, we instead append new tuples discarding the previous tuples as old and only reading from the new tuples

in log structured approach we use the concept of logs instead of tuples. A log is basically something that records changes in a tuple. Example

PUT(X1, 1001)
PUT(X2, 2001) 
PUT(X1, 3001) --> here instead of overwriting an already existing tuple, we add a new log entry that has the new change

The main operations of log structured storage is PUT and DELETE

and this works on the basis of two main data structures
[[memtable-database]] and [[SSTables-database]]


