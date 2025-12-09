```
provider "aws" {
	region = "us-east-2"
}
```

- tell terraform to use AWS as its provider
- tell terraform to create all resources in the `us-east-2` region
- each region has multiple availability zones such as `us-east-2a`, `us-east-2b` and more

syntax for creating a resource in terraform
```
resource "<PROVIDER>_<TYPE>" "<NAME>" {
	[CONFIG ...]
}
```

to deploy an EC2 instance, use the aws_instance resource

```
resource "aws_instance" "example" {
	ami = "ami-0fb653ca2d3203ac1"
	instance_type = "t2.micro"
}
```

terraform keeps track of all the previous changes it created, so for example i just did a `terraform apply` to create a new ec2 instance and modified some funtionality such as name of the instance then it will not create a new server but use the existing server listed in the configuration