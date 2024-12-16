- the contents of an docker image are stored in `/var/lib/docker/overlay2` directory in linux
- after performing a `docker pull ubuntu` , it creates a single fs layer inside our `/var/lib/docker/overlay2` directory with a image layer identifier and a `l` (lowercase L) directory
- the `l` directory contains shortened layer identifier as symbolic link
- the lowest layer contains a `link` and a `diff` directory, the `link` directory contains the shortest symbolic link as its value and the `diff` directory contains the layers' content

- the lower layer is the first layer or the base layer of an image which in most container is the base OS filesystem 

- when we add new layers by changing either the `Dockerfile` or my `docker container commit` it creates new directory entries in `/var/lib/docker/overlay2` 
- these new layers are called upper layer and contains content like `link`, `diff`, `lower` where `lower` contains a link to its parent layer or the base layer in this case. 
- A `merged` directory contains the merged contents of itself and its parent layer. this is usually a different directory than the `upperdir` and `lowerdir`

