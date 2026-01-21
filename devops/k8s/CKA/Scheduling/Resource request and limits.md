control how much cpu and memory the running container can consume

### resource request
requests specify the minimum amount of resource a container needs to run. kubernetes uses this information to place a pod to a node that meets this resource request criteria

**How requests work:**
- The scheduler uses requests to find a node with enough available resources
- If no node has sufficient resources, the pod remains in "Pending" state
- Requests are guaranteed to the container—it will always have access to at least this amount
- Multiple containers on the same node can have overlapping requests, but the scheduler ensures the node has capacity

```
resources:
  requests:
    memory: "256Mi"
    cpu: "500m"
```

Mi = mebibytes of memory 
1 kibibyte (KiB) = 1,024 bytes
1 mebibyte (MiB) = 1024 * 1024 bytes

m = millicores

1 CPU core = 1000 millicores
1 millicore = 1/1000 of a CPU core
500 m  = 0.5 core

in a 4 core machine, 1000m means you can use 100% of one core, which would mean 250m would mean you can use 25% of one CPU core
on cloud providers, this refers to virtual CPUs (vCPU)

### resource limits
maximum amount of resource a container can use, this is a upper bound which cannot be exceeded
**How limits work:**

For **CPU limits:**
- The container is throttled if it tries to use more CPU than its limit
- It won't be terminated, just prevented from using additional CPU cycles
- CPU is a "compressible" resource—throttling doesn't kill the process

For **memory limits:**
- If a container exceeds its memory limit, it becomes a candidate for termination
- The kernel's OOM (Out of Memory) killer may terminate the container
- Memory is a "non-compressible" resource—you can't throttle memory usage

```
resources:
  limits:
    memory: "512Mi"
    cpu: "1000m"
```

### Full example

```
apiVersion: v1
kind: Pod
metadata:
  name: my-app
spec:
  containers:
  - name: app-container
    image: my-app:1.0
    resources:
      requests:
        memory: "256Mi"
        cpu: "250m"
      limits:
        memory: "512Mi"
        cpu: "500m"
```


### default behavior 

by default, kubernetes does not have a CPU or memory request or limit set 
which means any pod can consume as much CPU or memory that is available and required

- no requests, no limits
if we want to schedule two pods then one pod can consume all the CPU resources on the node and prevent the second pod of required resources 

- no request, limits
kuberentes automatically sets requests as same as limits

- requests, limits
if pod one is requires more cpu cycles and pod two isn't utilizing any resource then 