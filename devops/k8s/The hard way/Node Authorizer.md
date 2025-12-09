special authorization mode in kubernetes that controls what the kubelet (the agent running on each node) is allowed to do when it communicates with the API server

Worker nodes need to interact with the Kubernetes API server to:

- Read pod specifications assigned to them
- Update pod and node status
- Read secrets and configmaps for their pods
- Read services and endpoints

it ensures each node can only access resources related to pods running on itself
