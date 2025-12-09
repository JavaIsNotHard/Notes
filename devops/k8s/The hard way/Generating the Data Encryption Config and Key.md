in kubernetes, we can encrypt data at rest
**Data at rest** = Data stored on disk (as opposed to data in transit over the network)

In Kubernetes, this specifically refers to data stored in **etcd**, the database that holds all your cluster state, including:

- Secrets (passwords, API keys, tokens)
- ConfigMaps
- Resource definitions
- Any other cluster data

how to enable encryption??

use the type: EncryptionConfiguration 

To enable encryption, you must:
1. Create an encryption configuration file (YAML)
2. Tell the API server where this file is using the `--encryption-provider-config` flag
```
kube-apiserver \ --encryption-provider-config=/etc/kubernetes/encryption-config.yaml \
 ...other flags...
```

```
apiVersion: apiserver.config.k8s.io/v1
kind: EncryptionConfiguration
resources:
  - resources:
      - secrets
    providers:
      - identity: {}         # ← First provider = NO ENCRYPTION!
      - aescbc:              # ← This is ignored for new writes
          keys:
            - name: key1
              secret: <key>
```

here we define a Encryption Configuration for kubernetes `Secret` resource
it defines two providers
- identity
- aescbc

if `identity` is the first provider, then no encryption is applied
if anything else, then the encryption using that particular configuration is used

we can define different EncryptionConfiguration for different resource types