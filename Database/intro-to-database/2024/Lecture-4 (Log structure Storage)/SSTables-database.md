header to get offset to find where the key will be located in the file

each level in the sstable is composed of multiple files  
each file contains the actual key and value data

a summary table contains both the min/max key and the bloom filter  
min/max key is found per sstable and bloom filter is used per level