The worlds simplest database 

```bash
#!/bin/bash

db_set() {
	echo "$1,$2," > database 
}

db_get() {
	grep "$1," database | sed -e "s/^$1,//" | tail -n 1
}
```

The above code stores as key value pair where $1 is the key and $2 is the value in a file called database. 

We can also retrieve the file using db_get() function by the key $1

This storages the value as plain text where the key value are separated by commas (,)

![[Screenshot 2024-10-19 at 08.00.23.png]]

This is a log-structured approach because we only append to the file 

The set operation is fast whereas the get operation is slow because we have to scan the file from the top to bottom and then check for the key 

This is way we need an index, index -> keep additional metadata on the side, different index have different search patterns, index slows down write because we need to add the new item to the primary database as well as the index

We as application developer need to know our query pattern i.e is it write intensive or read intensive, how users search for data 