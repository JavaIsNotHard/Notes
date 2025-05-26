in microservice architecture it is a best practice to have a single container running a single service in a single pod but there are cases where we can run multiple containers in a single pods that are related. for example, we could have a sync and serve pod which contains a sync container which sync its content with a remote server and a serve container which reads the content synced by the sync container, the sync container writes its latest data into a shared volume which can be directly accessed by the serve container

Kubernetes have two main patterns for multi-container pods
1. [[init container]]
2. [[sidecar container]]