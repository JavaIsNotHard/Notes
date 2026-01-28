used to scale in or scale out aws resources such as ec2 based on the current load the system is going through

for a auto scaling group, we define the following
- minimum capacity
- desired capacity
- maximum capacity

if the current is < maximum capacity then we can scale out the current ec2 instance

based on the health check performed by the ELB, the ASG can also terminate unhealthy ec2 instances that the ASG are handling


to configure the ASG, we need to specific a launch template
the launch template contains all the information about the instances such as AMI, name, subnet, security groups and many more


### Auto scaling with CloudWatch alarm

we create a custom metric based on which the cloudwatch alarm will be triggered
for example, if the average CPU usage spikes up to some number then scale out
if the average CPU is below some threshold then scale in

scale out policies
scale in policies


### Scaling policies

- dynamic scaling
	- target tracking scaling: 
		- define a threshold metric and if the threshold is exceeded then scale out
		- if the current metric is below the threshold then scale in
	- step scaling:
		- define steps based on metric ranges such as CPU utilization from 40% - 60% -> add 2 instance
		- CPU > 80% -> add 3 instances
		- CPU < 10%  -> remove 1 instance
- scheduled scaling
	- scaling based on time of the day
	- we define a time when the scaling should occur
	- scale out at 10pm or scale in at 5am and so on
- predictive scaling
	- the ASG analyses the historical metrics of the server, how the request arrive at the server and so on and based on this historical metrics, the ASG performs machine learning to create a forecast and based on which scaling is performed

metrics to scale on
- CPU utilization
- request count per target
- average network in/out


### Scaling cooldown

after a scaling activity has occurred then the ASG enters a scaling cooldown period
during the cooldown period, the ASG will not add or remove instances, so no actions will be performed 

using ready-to-use AMI will reduce the configuration time to start the instance