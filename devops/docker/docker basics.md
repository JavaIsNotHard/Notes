## docker commands
- [[docker run]]
- [[docker pull]]
- [[docker exec]]
- [[docker attach & docker start]]
- [[docker container commit]]
- [[docker volume]]

## docker overview
- [[how images and overlayfs work in docker]]


- `docker run --rm` will perform `docker kill <container-name>` and `docker rm <container-name>` when host machine sends SIGKILL signal to the container i.e CTRL+c

- alpine container do not have bash by default but have sh and are also lightweight in comparison to ubuntu containers 

- if no changes are found during docker run then the previous docker images are used to execute Dockerfile instructions

- all instructions in Dockerfile except CMD are executed during build time i.e when we do `docker build . -t <name>`
- CMD is executed when we call docker run, unless we overwrite it with other commands using docker run or docker exec

- ENTRYPOINT in docker is basically `bin/sh -c` followed by whatever is in the CMD, we can obviously overwrite this value using the `ENTRYPOINT []` inside the docker file 

- ways to set the ENTRYPOINT and CMD in docker 
	- exec form -> `ENTRYPOINT [<something>]`
	- shell form  -> `ENTRYPOINT <something>`
![[Screenshot 2024-12-27 at 5.54.14 PM.png | 500]]


## Docker Digest
- using tags pull images can have some problems for example when we incorrent name the tag number for an image 
- we can push the new image to the same repository with the same tag as the vulnerable image which means if we have multiple machines running container with the same tag number, we cannot say whether it is safe or not 
- image digest uses content addressable storage which gets a cryptographic content hash that we usually call a digest 
- this way no two different images that have different contents have the same hash digest 
- `docker images --digests alpine` shows the image digest of the image named alpine 

## Multi architecture images 
- `docker buildx imagetools inspect alpine` shows the manifest list and manifest file of the image 
- manifest list -> a high level index that docker uses to refer to multiple image manifests for different architecture 
- manifests -> each manifest specifies 
	- platform 
	- digest 
	- layers 



- `docker exec` command is used to send arguments to the container
- `docker inspect` command is used to give full detail about a running container, it can also be used against images to give full details about an image 



## Containerizing a single container app 
- `docker init` command can be used to generate Dockerfiles based on the current application structure and framework, programming language used 
- `docker build .` command builds an image based on the Dockerfile using either a local builder or a remote builder 
- instructions that create new layers include FROM, RUN, COPY and WORKDIR
- these instructions add new layers on top of the base OS layer
- instructions that create metadata include EXPOSE, ENV, CMD and ENTRYPOINT 

## pushing  image to docker hub
- `docker login` is used to login to docker hub and authenicating the machine 
- `docker tag <current_tag> <new_tag>` is used to rename a tag for an image 
- `docker push` pushes the image to the hub
- `docker history` is used to show all the commands that created that image 

## Multi stage builds
- minimizing the size of the final image by building the image in multiple stages 
- the first stage is the base stage which pulls the OS layer, copies all the needed files from the host machine and downloads all the dependencies needed for the application
- the second stage is to compile the application using the image build from the first stage (it contains everything needed to compile the application into binary)
- the last stage is to create a scratch image and copy the container into that scratch image 

## Buildx, BuildKit and drivers 
- behind hte scenes, Docker's build system has two components 
	- Client: Buildx
	- Server: BuildKit
- ![[Screenshot 2024-12-31 at 6.48.45 PM.png|500]]

- when we use the `docker build` command then the buildx sends the command to either the cloud driver or buildkit (local builder)
- we can see the currently selected builder using the command `docker buildx ls`
- we can inspect a builder using the command `docker buildx inspect <builder name>`

## Multi-architecture builds

