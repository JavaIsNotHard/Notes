```
apiVersion: v1
kind: Pod
metadata:
  name: config-env-pod
spec:
  containers:
    - name: app
      image: busybox
      command: ["sh", "-c", "env | grep APP && sleep 3600"]
      envFrom:
        - configMapRef:
            name: app-config
```

using the entire configmap resource stored in etcd storage 

```
apiVersion: v1
kind: Pod
metadata:
  name: config-file-pod
spec:
  containers:
  - name: app
    image: busybox
    command: ["sh", "-c", "cat /config/app.conf && sleep 3600"]
    volumeMounts:
    - name: config-vol
      mountPath: /config
  volumes:
  - name: config-vol
    configMap:
      name: app-file-config
```

mount configmap as a volume

we can edit the value of a configmap that has already been created using the following command
```
kubectl edit configmap app-config
```
