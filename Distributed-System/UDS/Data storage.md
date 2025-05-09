
## NoSQL 

white papers such as Bigtable and Dynamo revolutionized the industry and started a push towards scalable storage layers

the first generation of these data stores didn't support SQL hence they were referred to as NoSQL 
but NoSQL nowadays have evolved to support features like dialects of SQL that used to only available in relational data stores

relational databases support stronger consistency models such as strict serializability, NoSQL stores embrace relaxed consistency models such as eventual and causal consistency to support high availability

NoSQL stores generally don't provide joins and rely on the data and are represented as key-value pairs or documents such as JSON

difference between key-value and document store?

the difference is that documents are interpreted and indexed and therefore can be queried based on their internal structure

NoSQL stores natively support partitioning for scalability purposes, they have limited support for transactions

the main requirement for using a NoSQL data store efficiently is to know the access patterns upfront and model the data accordingly 


Dynamo DB key consists of either a single attribute, the partition key or of two attributes, the partition key and sort key
partition key -> how data is partitioned and distributed across nodes
sort key -> defines how the data is sorted within a partition which allows for efficient range queries

architecture DynamoDB is very different from the one presented in the Dynamo paper, at a high level, dynamoDB's API supports
1. CRUD operation on single items 
2. querying multiple items that have the same partition keys
3. scanning the entire table

join operations are not presented since they don't scale well instead we should model our data such that we don't require joins in the first place

dynamoDB also supports secondary indexes for more complex access patterns
local secondary index allows a different sort key but the same partition key 
global secondary index allows for different partition and sort keys

but GSI is asynchronous because waiting for the global secondary index to be consistent with the main table would cause performance issues hence they are made consistent in the background and as a result they only provide eventual consistency guarantee

because NoSQL stores are tightly coupled to their access patterns, they are a lot less flexible than relational databases
so to work or use NoSQL we need to first identify the access pattern upfront to model the data accordingly