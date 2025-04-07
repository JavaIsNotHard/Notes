init -> dockerd -> containerd -> containerd-shim & runc -> prctl & unshare -> clone 
what does clone?
based on the clone based specified on the unshare system call, the clone sys call will create new child process and fake the resources such as PID, network, mount and more to provide isolation inside this process
