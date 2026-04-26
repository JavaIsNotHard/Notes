
place where we store our terraform state files

default : local state file
remote : Amazon S3, HashiCorp's Terraform cloud

remote backend solves the following problems
1. no manual error: developers don't need to remember to pull the latest state files or the latest code. They are managed by the provider themselves. So it will automatically store the new state file after each `apply` command

2. locking : remote backend supports locking when running `terraform apply`

3. Secrets : remote backends support encryption at rest and in transit. also has feature for permission based access through IAM policies if S3 is used


### S3 as a backend

With this backend enabled, Terraform will automatically pull the latest state from this S3 bucket before running a command and automatically push the latest state to the
S3 bucket after running a command

using dynamodb table with s3 backend also makes it possible to acquire lock before any `apply` and `plan` statement to prevent multiple developers from changing the state file at the same time