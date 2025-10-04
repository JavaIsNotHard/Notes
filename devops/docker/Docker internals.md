- [[docker/namespace]]
- [[chroot]]
- [[cgroups]]
- [[overlayfs]]


[[what are containerd and runc in docker]]

containerd invokes shim process which then calls the runtime that implements the OCI specification
shim invokes the runtime

what does containerd do?
containerd lays out the container's filesystem, and creates the necessary config information
and invokes the shim process

why the shim and not invoking the runtime directly?
The separate "shim+engine" pattern is used because it makes it easier to integrate distinct runtimes implementing a specific runtime engine spec, such as the OCI runtime spec

the flow is something like this:
1. containerd receives request to create a container
2. then it lays the container's filesystem and creates the necessary container configuration
3. containerd invokes the shim, including the container configuration which is used to decide whether to create a socket to listen (1:1 shim to container) or use an existing one (1:many)
	1. if existing socket it used then it returns the address of the existing socket and exits
	2. if new then, shim:
		1. creates a new process to listen to a socket for ttRPC commands from containerd
		2. returns the address of the socket to containerd and exits
4. containerd sends command to create a container 
5. the shim invokes the runc binary to create/start/stop the container
