there might exists multiple leaf nodes with the same key which means the scanner must traverse the entire leaf node to get all the keys with the same value which could result in a sequential scan of the leaf node making it slow

the index lookup not only needs to perform the tree traversal, it also needs to follow the leaf node chain


