- the index not only has to traverse the tree but also has to follow the [[leaf node chain]]
- the table data is scattered across the disk which means that if we were to access one disk item pointed by the index leaf node then we might have to wait for the disk arm to reach for another node that may be in another disk block far from the previous one. This problem happens because we are storing pages in heap file which is unordered.

- the first case happens when we are returning a large number of rows using index, typically when using WHERE clause
- the second case happens when we create index on a column that is not unique. this can be avoided when we are searching for items that are part of primary keys since primary keys are mainly unique

types of index operation in oracle database:
1. index unique scan: the fastest index operation, tree traversal from root to leaf node. used when db knows with certain that only one row can match typically because you are searching on a primary key or a unique constraint
2. index range scan: after the initial tree travesal to find the starting point of the leaf node, the db must also follow the doubly linked list sequentially to find other matching nodes
3. index table scan: the real performance killer, for each rowid during the index scan, the db must perform a separate IO operation to fetch the actual table row from the heap, if the rows are scattered randmly acrsoo data blocks, this means random IO for every single row


what is clustered index and a non-clustered index?
- the order in which data is stored on disk is maintained by the clustered index while non-clustered index does not maintain the how data is stored on disk
- the leaf node of clustered index points to the actual tuple inside a page whereas non-clustered index points to the location where the data can be found not the data itself.

- the database creates indexes for primary key of the table even if we do not use `create index` command.
- we can also create indexes with combination of multiple columns called concatenated index or composite index.
- the first column of the composite index is used to sort the index whereas the second, third and other columns are used to perform range search over the possible values of key=column1.

- `INDEX RANGE SCAN` -> this is used when there is a range query. For example `where col 1 = 10 && col 2 = 20`. This query first searches through the index for `col 1 = 10` and then ranges over all possible `col1 = 10` having corresponding `col2 = 20`. This only happens when we use composite index.
- `INDEX UNQIUE SCAN` -> this is used when we are searching for a unique column in the table.  for example, `where col1 = 10`. if `col1` is primary key and has uniqueness constraint then we will only have one possible value of that key.
- `TABLE ACCESS FULL` -> searches all the values of a table one after another. This is the worst case scenario when executing a query.
- `TABLE ACCESS BY ROWID` -> Once we get the `rowID` from the index, then we use that row to get the next column value. for example, ``SELECT col1, col2 FROM my_table WHERE col1 = 10;`` , the index would use the `rowID` retrieved from `col1 = 10` and find the corresponding `col2` value.

- to define an optimal index, we not only need to know the working of the index we are using but also the queries our application will be facing. we need to know the combinations that appear in the where clause.

- The query optimizer 

- using index on the correct search column. 
- if we have index on the wrong column then `full table scan` can sometimes have better performance than `index range scan`