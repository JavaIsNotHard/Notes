- sits between the [[containerd]] and OCI runtime such as [[runc]]
- when [[runc]] creates a new container, it exits and shim is made the parent process of the container just created
- shim and [[runc]] are both forked by [[containerd]] for every new container 
- it reports container status and keeps the container's STDOUT and STDIN open 
- 