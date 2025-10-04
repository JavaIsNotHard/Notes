The main idea of external merge sort is to sort data out of memory which in the case of database would be sorting the data on disk 

external merge sort is similar to our merge sort algorithm but the data have to be brought back and forth from disk to memory 

first we have a large chuck of dataset residing in the disk, the disk is then divided into smaller subsets called runs 

the runs are then brought into memory and sorted inplace? and then written back to disk and then the sorted runs are combined to create a larger sorted dataset 

In the sorted run the possible values includes:
1. tuple (early materialization) : this way we bring the entire tuple value with us when sorting the key
2. record ID (late materialization) : we only have a reference to the record using the record ID and then get the value from the disk when all the filters and operators have been performed
