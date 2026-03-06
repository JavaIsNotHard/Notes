
server certificates for servers (server public key & private key)
client certificates for client
and root certificates

all communication between the components has to be secured through TLS

clients that interact with the cluster (kubectl -> kube-api-server) must also communicate using TLS

clients in kubernetes components include the following:
- admin (kubectl)
- kube-scheduler
- kube-controller-manager
- kube-proxy

servers in kubernetes components include:
- api-server
- etcd server
- kubelet

api-server is the only component that interacts with the etcd-server
also api-server performs a bidirectional communication with etcd-server and kubelet

which means the api-server requires separate key for authentication with etcd server and kubelet

something like kube-api-server-etcd-server.crt and kube-api-server-kubelet.crt and so on

the api-server itself requires withs own certificates and keys such as kube-api-server.crt and kube-api-server.key

why??

- When kubectl, kubelets, or other components connect to the API server, they need to verify they're talking to the legitimate API server and not an imposter
- The API server presents its certificate, which clients validate against a trusted Certificate Authority (CA). This prevents man-in-the-middle attacks.


each component has a certificate and a key associated with it 
