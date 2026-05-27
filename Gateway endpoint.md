implemented as route table entry plus some hidden routing magic 


lets take an example of gateway endpoint implementation with s3 

1. AWS creates a prefix list containing the public IP ranges that S3 own in that region. The list is updated automatically as S3's IP changes 
2. AWS adds route to the route table where each route contains a mapping between the S3 prefix list and the vpc endpoint. Example, suppose the mapping is called pl-63a5400a and the vpc endpoint id is vpce-1234abcd then we have a mapping with the entry `pl-63a5400a → vpce-1234abcd`
3. 
