managed NFS (network file system) for general workload
use of security group to control access to EFS
compatible with linux based AMI

uses POSIX and has standard file system API
file system auto scale, pay per use for each gigabyte of data used in EFS

![[Pasted image 20251203215630.png | 400]]

EFS performance 
1. can scale up to 1000+ concurrent NFS clients, 10+ GB/s throughput
2. Grow upto petabytes of data

performance modes
- performance mode deals with the following
	- latency
	- throughput
	- operations per second
	- when you create an EFS, you choose one of the following performance modes:
		- general purpose: provides the lowest latency per operation (quick for individual reads and writes). Default mode and great for general workloads such as web servers, CMS, shared file directory etc
		- MAX I/O: designed for highly parallel workloads, many clients/threads/instances accessing the EFS at the same time or concurrently. produces more latency

Throughput mode
- refers to much data transfer capacity the file system provides to clients
- throughput = the rate at which data is transferred between the file system and the client
- supports 3 modes
	- bursting mode:
		- throughput scales automatically with the size of the file system
		- you have a baseline of 50 MiB/s per TB of storage which means that if we use 100 GB of storage then we get a throughput of 5 MiB/s and this speed can burst upto 100 MiB/s
		- this is best for workloads that produces spikes in activity
	- provisioned throughput:
		- you specify the exact throughput you need independent of the storage size
	- elastic throughput:
		- automatically scales throughput up and down based on the workload
		- can scale higher than bursting mode

EFS storage class
what is storage class??
helps decide which storage to use based on the performance and price of each storage class based on your workload, 


different storage class have different access pattern and performance and lifecycle management option helps us to transition from one access method to another 
