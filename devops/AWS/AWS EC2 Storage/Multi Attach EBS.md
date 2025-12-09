- attach the same EBS volume to multiple EC2 instances in the same AZ 
-  only available to the io1 and io2 family of EBS volume

- why do we need multi attach EBS
	- high availability 
		- if we have two instances that share the same EBS volume then if one instance is down then another server can still access the data from the EBS volume
	- increased throughput
		- suppose an ec2 instance has a max throughput of 1000 MB/s, but an ebs volume supports 4000 MB/s which means we are not utilizing ebs to its fullest
		- now suppose we have 4 instances all simulatenously request the ebs volume, then the total throughput increases to 4000 MB/s
		- parallel I/O ports allow two or more request to be processed indepedenlty without context swithcing