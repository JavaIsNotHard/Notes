What are indexes?
They are replica's of a subset of table attributes. For example, if we have a table with attribute name, address and phone no. We could have an index on the attribute phone no since they are unique. Now the DBMS or storage engine needs to maintain a separate page which arranges the phone no attribute's value in a effective manner. 

What are the storage mechanism for a b+ tree 
Nodes of b+ tree corresponds to pages in the table 

Ordered vs unordered file pages 
We saw that in heap file organization such as a slotted page approach placed tuples wherever free space was available. An example of unordered tuple organization could be something like tuple with id 102 coming before id 20 or tuple with id 39 coming after id 203 and so on. 
The sequential file organization is an example of ordered file organization where one record will point to another sequential record in order. The records in sequential file organization are sorted based on some super key.

clustered vs unclustered index 
In clustered index the records of the table are arranged in the same order that the index records are arranged in. This is typically the case with ordered file system where the records are sorted based on some search key. 
Clustered index can either be enforced later after the index is made or the indexing can be done on the relation before adding data to it. This means that we create a clustered index on a relation or a table then this would add new items in the same order in which the index are filled. 

B+ tree data structure 

How to deal with duplicate key in B+ tree 
-> append record id in the end of the key of the B+ tree node 
-> store duplicate key as overflow pages

Concurrent indexes
- Concurrent hash indexes 
- Concurrent b+tree indexes 
