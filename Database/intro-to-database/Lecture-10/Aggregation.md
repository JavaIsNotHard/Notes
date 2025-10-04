what is we don't need the data to be sorted?
- if we are not ordering the data with the ORDER BY clause then we don't have to use sorting algorithms at all and since on disk sorting algorithms are slow we are better to avoid it
- sorting is not required for JOINS, GROUP BY and DISTINCT clause 

so instead we can use a hashing technique to do the computation for us
when using hashing techniques we can scan through all the records in the table and hash the key or the column that is present in the query and then create bucket for that hash value. we do this for each record in the dataset,

Computing aggregates for:
- GROUP BY: we hash the key and if the hash is already present in the bucket then update the aggregate if not we create a new bucket 
- DISTINCT: we again hash the key and if the hash is already present then we skip the key but if it not not present then we add it to the result set

this is assuming that the dataset fits in memory, but that is not always the case with big dataset where we may have to spill data on disk 


