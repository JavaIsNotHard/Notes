2 way means that at one time we will work with 2 runs of data i.e 2 chucks of data. represents the number of runs that we are going to merge into a new run for each pass

the dataset is broken down into N pages
B is the number of pages that we can buffer in memory for in memory sorting. the value of B can be set as a database configuration that it uses during its runtime 

Steps

1. Pass #0
	You bring pages from disk to memory (1 page at a time most of the time) you sort that page in memory and write it back to disk. This happens for each page that we want to sort.
2.  Pass #1, #2, ....
	You read the sorted individual pages from disk again back to memory mainly 2 pages since this is a 2 way external merge sort then we scan through both the sorted pages one item at a time and merge them to create the output page which is also buffered in memory and then written back to disk 

the number of passes = 1 + ceiling value(log base 2 (N))
total I/O cost i.e number of times data is read and written to disk = 2 * N * No of passes

double buffering optimization


