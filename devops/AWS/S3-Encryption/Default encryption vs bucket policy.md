if we have a bucket policy in place then the bucket policy is evaluated before the default encryption is applied to the object

suppose we have a rule that says
- Deny any upload that doesn't use SSE-KMS

and if suppose that the user request doesn't have the encryption header then the request is dropped or denied

but if the bucket policy is not present then the request is automatically encryption using default encryption by S3