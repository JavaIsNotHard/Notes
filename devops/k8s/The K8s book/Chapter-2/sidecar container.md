sidecar containers are mainly used in service mesh where it is used to monitoring, filtering, logging and other side acitivities of the application

we define a sidecar container similar to how we define a [[init container]] but with a restartPolicy set to Always, doing this ensures following:
1. the sidecar container starts before the application container
2. runs alongside the application container 
3. terminates after the application container

