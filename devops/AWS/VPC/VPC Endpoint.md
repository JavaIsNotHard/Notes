there are some AWS services that are not inside the VPC
they live in the public infrastructure and are reachable via public IP

by default
packets between AWS resource to such AWS resource or services can go outside the AWS private network and into the public internet

one solution to this problem is to use the Internet Gateway which can handle public routes but the best solution is to use the VPC endpoint

what does the VPC endpoint do?

it creates a directly private link between the public resource and the private resource

Without VPC Endpoint: EC2 → Internet Gateway → Public Internet → S3
With VPC Endpoint: EC2 → VPC Endpoint → S3 (all within AWS private network)

There are two types
1. Gateway Endpoint
2. Interface Endpoint