Network layer 
- Deploying our RDS instance in a private subnet with no public access
- give no public IP to the RDS instance such that it cannot be connect over public network

Encryption layer
- encrypt the data stored on disk using AWS KMS (key management system)
	- requires this option to be toggled when the db is created and cannot be toggled once the db has been created
	- if we have to encrypt an already running db instance then we have to first create a snapshot and restore the data with encryption toggled
- RDS can also use encryption in transit i.e TLS encryption

Authentication layer
- use user / password authentication
- use AWS IAM roles / username instead of username and password
	- generate short lived tokens such that application can use this short lived token instead of hardcoding the credentials

Secrets Manager
- store and automatically **rotate DB credentials** on schedule such that apps can fetch the rotated key and secret from the secrets manager without hardcoding a static password

Monitoring
- monitoring api calls, queries ran, OS metrics, database activity log stream

IAM policy & DB level privileges
