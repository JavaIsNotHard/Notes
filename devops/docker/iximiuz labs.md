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
