
AWS VPC

the foundational network construct in AWS is VPC (Virtual Private Cloud)

each VPC is assigned to an AWS region 

each region has at least 3 availability zones (AZs)

AZ are physical vessel containing compute and network infrastructure in a minimal geographical area 

AWS has segmented a VPC into subnets living inside an AZ

VPC is regional and network is software defined 

some VPC components that are configurations rather than physical device that can work across multiple AZs. Example is route table, since route table are just a collection of rules, we can attach the same route table along multiple subnets. These subnets may be in different AZs

each subnet belongs to a single AZ and a single subnet cannot span multiple AZs

![[Pasted image 20260218155447.png]]
