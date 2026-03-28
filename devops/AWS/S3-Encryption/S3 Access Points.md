basically its used to segregate the responsibility of user polices to itself rather than to the bucket as a whole 
![[Pasted image 20260312214607.png]]

- here, there are 2 folders in a bucket, finance and sales
- the finance folder can be accessed only through the finance access point and analytics access point
- the sales folder can be accessed only through the sales access point and analytics access point

each access point will have its own R/W polices granted to it such that user or role without that policy are rejected from the bucket

S3 Access Points provides with its own DNS name and policies