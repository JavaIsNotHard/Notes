- docker is not a VM (virtual memory)
- chroot on steroid
- cgroups and namespace

## Control groups 
- used to control, manage and monitor the resource utilization of various subsystem by a process 
- subsystem includes memory, cpu, disk I/O and more 

## Namespace 
- makes a process within a namespace that they have their own isolated instance of the global resource
- the parent process of the namespace process can view all the process running in them but not vice versa
- there are various types of namespace that can be used depending on the flag that we provide when creating them

# Container Network

communication between the host and the container namespace happens using veth pairs 

communication between container to container happens using bridge network interface

communication between container in one host to another happens using the routing table and the LAN switch between them which is a direct communication and requires no manual intervention

communication between container to container with separate L2 network or communication over the internet happens with the help of overlay network