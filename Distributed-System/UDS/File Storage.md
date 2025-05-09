CDN reduces the number of request hitting the application server
but the servers' storage is limited and will run out of space soon, this is why a file storage like AWS S3 or Azure Blob Storage are used to store large static files 

these file stores offers scalability, high availability and strong durability guarantees
each file are allowed for the public access by associating a URL with the blob without authentication
you can then configure the CDN directly fetch the blob directly from the URL 
this offloads the storage and serving of static resources because storage will be managed by the blob storage like S3 and serving is done through the CDN

## blob storage architecture

Azure storage provides strong consistency
files are referred to as blob store

Azure storage is composed of storage clusters distributed across multiple regions worldwide 
a storage cluster is composed of multiple racks of nodes where each rack is built out as a separate unit with redundant networking and power which means that each rack is composed of its own network and a separate power supply such that if one of the rack is down that doesn't affect other racks and can continue to operate on failure 

Azure storage exposes a global namespace to identify each blob which is composed of the Account name and the file name

A central location service acts as a global control plane in charge of creating new accounts and allocating them to clusters and also manage moving them from one cluster to another for better load distribution

the architecture of a cluster is divided into 3 layers which includes
1. front-end layer 
2. partition layer 
3. stream layer 

stream layer is responsible for storing files in a sequential append-only manner where data are called as streams
streams are broken down into extends 
extend is a unit of replication or blocks in file system that are fixed size chucks 
writes to extends are replicated synchronously through chain replication
unit of replication meaning that this is what is replicated rather than the stream 
the extents are replicated in multiple storage servers and those are synchronized with each other using the chain replication protocol

a stream manager is responsible for assigning an extent to a chain of storage servers in the clusters
when the stream manager is asked to create a new extent then it replies with a list of storage servers that hold a copy of the newly created extent
they are also responsible for handling unavailable or faulty extent replicas by creating new ones and reconfiguring the replication chains they are part of

partition layer is responsible for translating high level file operation into low level stream operation
partition layer has a partition manager which is responsible for managing a large index of all files stored in the cluster
each entry in the index contains metadata such as account and filename and a pointer to the actual data in the stream service
the partition manager range-partitions the index itself and maps each partition to a partition server
The partition manager is also responsible for load-balancing partitions across servers, splitting partitions when they become too hot, and merging cold ones

the partition layer also asynchronously replicates account across clusters in the background

the front-end layer acts a reverse proxy that authenticates requests and routes them to appropriate partition server using the mapping provided by the partition manager



