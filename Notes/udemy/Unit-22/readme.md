# Internal working of postgres


## Where does postgres store data in the machine?
Using the `SHOW data_directory` will return the path to where the data directory or the directory in which postgres stores its data is located at. In case of Unix system, they are usually placed under `/var/lib/pgsql/data`. This is also the same directory that the postgres user uses as the postgres directory. Inside the data directory we find various other directories which includes a `base` directory and this is the directory in which all the information about various databases are stored at. The databases are not stored as the name assigned during its creation but rather using a `oid` which uniquely identifies each database.
We can then use the value stored at the table `pg_database` to see the `oid` and the database name using the query `SELECT oid, datname FROM pg_database;`
Now to make more sense out of the files that are inside the oid directory we can use the query `SELECT * FROM pg_class;` to return a ton of value related to the objects inside the database. The object contains information about various things including each individual table that we create using `CREATE TABLE <name of table>` query.
The name of the table is listed as relname and along with the name the row also has a oid value which is the name of the file containing information about the table. 
This file is referred to as the `heap file`. The heap file contains a bunch of blocks or pages which in turn contains a each individual rows inside of them. Each block is of 8kb in size regardless of the amount of data inside the block. Remember, a block contains various rows inside them. 

## NOTE: the `pg_class` table contains information about all the objects inside the table in a database 

## Why is the size of each block of size 8kb?


## NOTE: will discuss more on the internal working of postgres after the end of this course by referring to other online documentation for more depth
