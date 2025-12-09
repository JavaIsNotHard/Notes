- elastic block storage volume is a network drive that you can attach to an instance to persist information the way you persist information using local ssd or hdd

- they are like local storage device but in the AWS environment, they are connected through internet

- They can be thought of as a "network USB stick"

- They are AZ bound which means that a EBS volume can only be mounted to an EC2 instance in the same AZ, to move a volume from one AZ to another, we need to first create a snapshot out of the volume and then use the snapshot in another volume

- A single EBS volume can only be mounted to a single EC2 instance 

- By default, an EC2 instance has a EBS backed root volume which stores information such as OS, system libraries and more which are needed for the AMI

- Also by default, EBS backed volumes are deleted on EC2 instance termination

- Before we initialize the volume, we need to provision it, meaning that we need to define its performance and capacity
![[Pasted image 20251129130722.png]]

- a single EC2 instance can have more than one volume attached to it, mainly as a primary and secondary volumes, the primary volume is called the root volume and by default the root volume are deleted on termination of the ec2 instance but any other volumes are not deleted

## Use the volume after attaching to the instance


![[Pasted image 20251129131929.png]]

![[Pasted image 20251129131947.png]]

![[Pasted image 20251129132101.png]]

![[Pasted image 20251129132110.png]]

![[Pasted image 20251129132207.png]]
