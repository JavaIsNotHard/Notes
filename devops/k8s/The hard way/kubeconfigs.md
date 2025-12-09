![[Pasted image 20251204203339.png | 300]]

```
apiVersion: v1
kind: Config

# Define WHERE you can connect (clusters)
clusters:
- name: prod-cluster              # Label A
  cluster:
    server: https://10.0.1.100:6443
    certificate-authority-data: PROD_CA_CERT

- name: staging-cluster           # Label B
  cluster:
    server: https://10.0.2.100:6443
    certificate-authority-data: STAGING_CA_CERT

# Define WHO you can be (users/credentials)
users:
- name: alice                     # Label X
  user:
    client-certificate-data: ALICE_CERT
    client-key-data: ALICE_KEY

- name: bob                       # Label Y
  user:
    client-certificate-data: BOB_CERT
    client-key-data: BOB_KEY

- name: readonly                  # Label Z
  user:
    token: TOKEN_123

# Mix and match: Connect to cluster A as user X, etc.
contexts:
- name: prod-as-alice
  context:
    cluster: prod-cluster         # References Label A
    user: alice                   # References Label X
    # Result: Connect to prod using Alice's certs

- name: prod-as-bob
  context:
    cluster: prod-cluster         
    user: bob                     
    # Result: Connect to prod using Bob's certs

- name: staging-as-readonly
  context:
    cluster: staging-cluster      
    user: readonly                

```

here we have defined two clusters
- prod-cluster
- staging-cluster

we also have defined two users:
- alice
- bob

we defined two contexts:
- prod as alice
	- cluster: prod-cluster
	- name: alice
- prod as bob
	- cluster: prod-cluster
	- name: bob
now the following of an authentication request is as follows

here is what happens when we enter `kubectl get pods` command

1. kubectl checks the current context
2. looks up the current context in the configfile
3. gets the cluster information as well as ca-authority-certificate, server info and more
4. gets the user information and user certificate and key
5. now kubectl knows where to connect to and how to authenticate
6. now makes authentication request to the cluster