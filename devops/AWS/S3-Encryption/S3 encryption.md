two types of encryption
1. server side encryption
	1. server side encryption with Amazon S3-Managed Keys (SSE-S3) (default)
		- uses the "x-amz-server-side-encryption": "AES256" HTTP header
		- encryption is performed using AES256
		- keys are handled and managed by AWS
		- default encryption method if encryption is enabled

		- the flow is something like this
			- user sends object + the encryption header
			- s3 uses its own key and encrypts the object and stores it

	2. Server side encryption with KMS keys stored in AWS KMS (key management store) (SSE-KMS)
		- uses the "X-amz-server-side-encryption": "aws:kms" HTTP header
		- s3 interacts with AWS KMS to encrypt the object and store it
		- limitation of KMS encryption:
			- multiple KMS API call to encrypt and decrypt the key

	3. Server side encryption with Customer provided keys (SSE-C)
2. client side encryption

We can force encryption in transit using the following resource policy in s3 bucket
```
{
	"Version": "2012-10-17",
	"Statement": [
		{
			"Effect": "Deny"
			"Principal": "*",
			"Action": "s3:GetObject",
			"Resource": "arn: aws: s3: ::my-bucket/*'
			"Condition": {
			"Bool": {
				"aws: SecureTransport": "false"
			}
		}
	]
}
```

this block all traffic originating from an HTTP url