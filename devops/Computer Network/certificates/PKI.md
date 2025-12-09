public key infrastructure, which is a framework for managing digital certificates and public key encryption
it contains the following components
- digital certificates 
- certificate authorities
- public/private key pairs
- certificate revocation

the root CA does not sign server or client certificates directly
the root CA delegates this responsibility to one or more intermediate CAs which are trusted by the root CA 


a root ca has the following data inside it
a index.txt and serial file which acts as flat file database to keep track of signed certificates

also it contains an openssl.conf file which configures the root CA for us
the root key (ca.key.pem) is created based on the configuration in the .conf file we create earlier
```
openssl genrsa -aes256 -out private/ca.key.pem 4096
```

using the root key we create the root certificate (ca.cert.pem)
Whenever you use the `req` tool, you must specify a configuration file to use with the `-config` option, otherwise OpenSSL will default to `/etc/pki/tls/openssl.cnf`.
```
openssl req -config openssl.cnf \
      -key private/ca.key.pem \
      -new -x509 -days 7300 -sha256 -extensions v3_ca \
      -out certs/ca.cert.pem
```

we can verify the root certificate using the following command
```
openssl x509 -noout -text -in certs/ca.cert.pem
```

we then create our intermediate CA keys, using the following command
```
openssl genrsa -aes256 \
      -out intermediate/private/intermediate.key.pem 4096
```

using the private key just generate, the intermediate CA creates a CSR using the following certificate
```
 openssl req -config intermediate/openssl.cnf -new -sha256 \
      -key intermediate/private/intermediate.key.pem \
      -out intermediate/csr/intermediate.csr.pem
```



the root CA signs the intermediate certificate, forming a chain of trust



CRL (certificate revocation list) is a published list of certificates that have been revoked before their expiration date and should no longer be trusted


chain of trust in certificates