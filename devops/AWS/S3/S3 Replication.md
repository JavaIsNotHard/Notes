CRR (cross region replication)
SRR (same region replication)

the replication happens asynchronously between the buckets
the s3 bucket must have proper bucket read and write IAM permission between s3 buckets

Only new objects are replicated 
can also replicate existing objects using s3 batch replication

for delete operation
- we can replicate the delete markers between the buckets 
- deletions of version ID are not replicated and are permanent to avoid malicious deletes

there is also no chaining of buckets i.e if 1 replciated to 2 and 2 replicates to 3 then 1 does not replicate to 3
