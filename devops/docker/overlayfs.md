- also known as union filesystem 
- divides the filesystem into layers 
- there is a base layer which contains all the necessary information to built the image 
- there are upper layers and lower layers
- lower layers are for read-only while upper layer can be used for both read and write 
- when the process reads, it reads from the upper layer, if the content is not found then it read from the lower below it and so on
- when a process writes, it writes to the upper layer as well
- the lower layer can be thought of as the base layer (in docker the base layer is mainly the OS base filesystem such as ubuntu ext4 base filesystem)
- any new changes made are made to the upper layer
- layers are used because they are recyclable i.e the same layer can be used for multiple containers such that we do not need duplicated information. For example we can have two containers that have the same base layer i.e OS filesystem
- the merge layer contains merged information between the upper and the lower layer


- the contents of an docker image are stored in `/var/lib/docker/overlay2` directory in linux
- after performing a `docker pull ubuntu` , it creates a single fs layer inside our `/var/lib/docker/overlay2` directory with a image layer identifier and a `l` (lowercase L) directory
- the `l` directory contains shortened layer identifier as symbolic link
- the lowest layer contains a `link` and a `diff` directory, the `link` directory contains the shortest symbolic link as its value and the `diff` directory contains the layers' content