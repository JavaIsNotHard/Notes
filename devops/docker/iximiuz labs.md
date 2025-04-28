# runc 
tools for spawing containers according to the OCI specification
it requires a bundle which should include a root file system and a configuration file i.e the OCI runtime sepcification


# OCI specification
containers cannot be processes but rather they are isolated and restricted box for running one or more processes inside it

according to the OCI ***runtime*** specification, to create a container, one needs to provide a runtime with  a filesystem bundle that consists of a config.json file and a container's filesystem 

OCI ***runtime*** specification defines container for the following platforms: linux, windows, z/OS, solaris and Virtual machines 

so config.json == common parts + platform-specific parts 

here common parts are common between the platforms and platform-specific parts differ between platforms i.e linux will have different features than windows and so on

the default config.json does not contains namespace and cgroups information because they are only for linux containers


# How Docker build works 
containers are needed to build images 



## how to run a container without an image 
we do not need a full linux distro to create a running container, we can just use the `FROM SCRATCH` which is an empty image and copy files into it
this approach is used by most docker linux distributions images like debian and such where they copy a file system into the scratch image's root directory
The OCI runtime specification does not mention the use of image to create container but its the other specification the OCI image specification does mention the use of images

Docker takes an image and converts it into a OCI bundle before invoking the low level runtime such as runc 
docker unpacks the image (images are stored in layers that are bundled in a tar archive)

why the need for images if we can create a container without using images?
- layered image structure 
- immutability of the layers

this allows for techniques such as content-addressable storage which basically helps us to refer to the checksum of the original tar rather than changing the same file again and again
reducing the need to duplicate the files
example: 
if we already have a ubuntu image installed in the local disk, its hash is also computed and stored to uniquely identify the content 
this makes sure that even if we pull the ubuntu image again, docker checks the hash and won't download it again since we already have that image 

if we create a dockerfile with `FROM ubuntu` as its base image then does not copy the entire file system into itself but rather it points to the existing ubuntu file system layer and then adds new layer on top of it

## You need containers to build images 

when we are building a docker image then surprisingly, docker launches containers for the execute of the instruction in the dockerfile i.e even to build the image we need a working container 

let's look at the implementation of the alpine image 
```
FROM scratch 
ADD alpine-minirootfs-3.11.6-x86_64.tar.gz / 
CMD ["/bin/sh"]
```

every time docker encounters a RUN instruction in the Dockerfile it actually fire a new container 
this container starts from the current state of the image i.e base image + all previous changes
when the execution of the RUN step completes, all the changes made to the container's file system becomes a new layer in the image and saves it 
docker then exits from this temporary container and moves to the next line in the dockerfile 


## creating a container using runc OCI specification
according to the OCI specification, we need a config.json file and a rootfs subfolder to create a container using runc 
the config.json file can be created using the command runc spec which dumps a default config.json file with some default options
the rootfs subfolder must contain a linux file system inside it
this is achieved by exporting a created but not started container's file system using the docker export command
````
docker export $(docker create ghcr.io/iximiuz/labs/nginx:alpine) | tar -xC <dest>
````

the `runc create` command didn't start the container based on the config.json file but rather just prepared the container 
it prepared a bunch of linux namespaces and used a `runc init` stub process to hold the namespaces together until the main application process starts

by default a new container is fully isolated from the outside world and the only network interface that exists in the network namespace is the loopback (lo) interface

to be able to access container from the host, we need to configure the virtual ethernet pair


## Reproduce a docker bridge network 

1. start a network namespace
	use the `ip netns` command to add, list and remove network namespace 
	example, `ip netns add container-1`
2. connect two network namespace
	to connect two namespaces, we need a path between them, this path is provided by the virtual ethernet pair between them, and it can be created using the command
	`sudo ip link add veth0 type veth peer name ceth0`
	here we create two virtual interface which acts as a pair where one pair will stay at the host namespace and the other needs to be moved to the container namespace
	to move the ceth0 interface to the custom namespace we use 
	`sudo ip link set ceth0 netns container-1`
	we also need to set the ip address and make the state as UP for the interface as follows
	`sudo ip netns exec container-1 ip link set ceth0 up`
	`sudo ip netns exec container-1 ip addr add 192.168.0.2/24 dev ceth0`
	the same should be done on the host side
	`sudo ip link set veth0 up`
	`sudo ip addr add 192.168.0.1/24 dev veth0`
3. connecting multiple network namespace through bridge network 
	basically create a bridge that routes all the request between the host to container and container to container
	create a bridge network using `sudo ip link add name br0 type bridge`
	and set up its ip address and state
	`sudo ip link set br0 up && sudo ip addr add 192.168.0.1/24 dev br0`
	Add the host's ends of the veth pairs to the bridge
	`sudo ip link set veth0 master br0 && sudo ip link set veth1 master br0`
	Add default routes to the containers to make the traffic flow through the bridge
	`sudo ip netns exec netns0 ip route add default via 192.168.0.1 && sudo ip netns exec netns1 ip route add default via 192.168.0.1`



now to reproduce a docker bridge network 