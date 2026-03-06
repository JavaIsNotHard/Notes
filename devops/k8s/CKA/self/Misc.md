when deploying metrics server in a kubernetes cluster through kubeadm, minikube or kind, the metrics server fails because it doesn't trust the self-signed certificates on the nodes.

**The Fix:** You need to pass the `--kubelet-insecure-tls` flag to the deployment.

for that you need to edit the deployment of metrics-server
```
kubectl edit deploy metrics-server


# and add this option
spec:
  containers:
  - args:
    - --cert-dir=/tmp
    - --secure-port=10250
    - --kubelet-preferred-address-types=InternalIP,ExternalIP,Hostname
    - --kubelet-use-node-status-port
    - --metric-resolution=15s
    - --kubelet-insecure-tls
```

we could also extract the default values.yml file like so

```
helm show values metrics-server/metrics-server > values.yaml
```

edit the file and apply our custom values like so

```
helm upgrade --install metrics-server metrics-server/metrics-server -f custom-values.yaml -n kube-system
```

