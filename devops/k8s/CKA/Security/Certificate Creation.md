
### Generating the Root certificate

we first need to provision our Certificate Authority (CA) which will have a self signed certificate

here are the steps

first we generate a key (private) using the following command
```
openssl genrsa -out ca.key 2048
```

then we create a certificate signing request using the following command
```
openssl req -new -key ca.key -subj "/CN="KUBERNETES-CA" -out ca.csr
```

the CSR has all the certificate information but no signature
here, in the CSR we specify the name of component in the CN (common name) field

then we sign the certificate using the following command
```
openssl x509 -req -in ca.csr -signkey ca.key -out ca.crt
```

the following is a self signed certificate which is signed using the CA's private key



for all other components, we will use the CA key pairs to sign their certificate

### Generating the admin user certificate (kubectl)

first we generate a key (private) using the following command
```
openssl genrsa -out admin.key 2048
```

then we create a certificate signing request using the following command
```
openssl req -new -key admin.key -subj \
	"/CN="KUBE-ADMIN/O=system:masters" -out admin.csr
```

we sign the certificate using the following command
```
openssl x509 -req -in admin.csr -CA ca.crt -CAkey ca.key -out admin.crt
```

how do we differentiate a admin user with other normal users in the authorization step of the request??
we add a group with administrative privileges with `/O=system:masters`


we do this step for all the client components such as scheduler, controller-manager and kube-proxy

when sending request to the api-server we have two ways to pass in the certificates
- directly accessing the apiserver with the following command
```
curl https://kube-apiserver:6443/api/v1/pods \
	--key admin.key --cert admin.crt
	--cacert ca.crt
```

-   using the kube-config file
```
apiVersion: v1
clusters:
- cluster:
		certificate-authority: ca.crt
		server: https://kube-apiserver:6443
	name: kubernetes
kind: Config
users:
- name: kubernetes-admin
	user:
		client-certificate: admin.crt
		client-key: admin. key
```


for the client component to validate a request or certificate send by the server, 
they all need a copy of the root CA's certificate


### Generating the server certificate

etcd server


