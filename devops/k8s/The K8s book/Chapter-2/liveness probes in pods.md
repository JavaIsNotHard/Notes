- used for checking container health
 - Kubernetes runs the probe periodically to ask the application if it’s still alive and well.
- If the application doesn’t respond, an error occurs, or  the response is negative, the container is considered unhealthy and is terminated.
- The container is then restarted if the restart policy allows it.

types: 
1. HTTP GET probe
2. TCP Socket probe
3. Exec probe: 
	- executes a command inside the container and checks the exit code it terminates with.
	- If the exit code is zero, the probe is successful.
	- A non-zero exit code is considered a failure. The probe is also considered to have failed if the command fails to terminate in time.

### liveness probe configuration

1. initialDelaySeconds
2. periodSeconds
3. timeoutSeconds
4. failuresSeconds

