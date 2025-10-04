the mainly used container runtime for kubernetes include docker and [[containerd]]

docker was first built before kubernetes and hence kubernetes was specifically developed to orchestrate docker

but there emerged other runtime such as rocket (rkt) which also wanted the functionality of kubernetes orchestration hence kubernetes developed the container runtime interface 

the cri allowed any vendor to work as container runtime for kubernetes as long as they adhered to the OCI specification or standards 

OCI standard contains a image spec and the runtime spec 
imagespec -> how image should be built 
runtimespec -> define how any runtime environment should be developed

but docker was built before kubernetes and hence did not adhere to the OCI specification
this is why kubernetes created a dockershim to continue support docker outside of the OCI


there are various command line tools that help to interact with containerD which includes
ctr, nerdctl and crictl
the crictl tool is used to interact with other CRI itself rather than just being limited to containerD

