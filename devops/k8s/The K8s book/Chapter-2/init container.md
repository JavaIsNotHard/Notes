it is a special type of container that starts and finishes before the main application workload program starts 
its purpose is to setup the environment for the application container to use 

example usage of a init container could be something like cloning a git repository that the application workload needs before starting the application program and moving the responsibility away from the application program. this makes sure that the application program can only focus on its own workload and defer the responsibility to the init container 

another example could the to check the availability of a remote API server before starting the container. the init container can be tasked to periodically sent heartbeat request to the remote API server to check for its availability and if they are available only then start the application program 

we can create a list of init containers that starts before the normal application container which we can list them in the Pod manifest. All the init containers must be completed before the application container can start and if any init container fails kubernetes attempts to restart it

one downside of init container is that it stops before the application container starts which means if we want a container that runs alongside the application container then we have to use something called a [[sidecar container]]

