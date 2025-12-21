
1. pod scheduled -> indicates whether the pod has been scheduled or not
2. initialzied -> all init containers have initialized completed or not
3. ContainersReady -> whether all container in the pod are ready
4. Ready -> the overall readiness of the pod to serve request


### Pod restart policy

1. always: Container is restarted regardless of the exit code the process in the container terminates with. This is the default restart policy.
2. onFailure: The container is restarted only if the process terminates with a non-zero exit code, which by convention indicates failure.
3. Never: The container is never restarted - not even when it fails.

when a pod restarts then with a NotReady or CrashLoopBackOff then each restart takes exponential backoff time between each restarts
![[Pasted image 20251219124755.png]]