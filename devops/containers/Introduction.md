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

