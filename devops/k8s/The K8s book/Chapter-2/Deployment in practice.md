```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: hello-deploy
spec:
  replicas: 10
  selector:
    matchLabels:
      app: hello-world
  revisionHistoryLimit: 5
  progressDeadlineSeconds: 300
  minReadySeconds: 10
  strategy:
    type: RollingUpdate
    rollingUpdate:
      maxUnavailable: 1
      maxSurge: 1
  template:
    metadata:
      labels:
        app: hello-world
    spec:
      containers:
      - name: hello-pod
        image: nigelpoulton/k8sbook:2.0
        ports:
        - containerPort: 8080
        resources:
          limits:
            memory: 128Mi
            cpu: 0.1
```

In this example YAML file we have defined a Kubernetes object of type Deployment which obviously wraps a ReplicaSet object and which itself wraps the Pod object 

the spec.replicas option tell the number of replicas to start in this deployment
spec.selector is used to select pods based on labels i.e Deployment only works with pods with the label hello-world

we can see that spec.selector and template.metadata.label have the same value which asserts the previous statement 

we also have the revisionHistoryLimit option which is set to 5 which tells Kubernetes to keep the previous 5 ReplicaSet object so that you can rollback to the previous 5 versions of the ReplicaSet

spec.progressDeadline option tells Kubernetes to give each new replica a 5 minute start window and if it takes more than 5 minutes to start, then update the status as stalled 

