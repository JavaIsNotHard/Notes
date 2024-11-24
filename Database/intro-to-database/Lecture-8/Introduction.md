- index vs filters 
- index tells exactly where the data is stored inside the heap file of our file system. index knows where the data is at whereas filters do not have this information.
- filters tells us whether the page has the value that we are looking for or not such that we do not sequentially scan that page for our value.

- other than the hash index, we have another data structure called the b-tree data structure 