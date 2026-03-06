
all user request either via the `kubectl` or via directly accessing the the api server through curl requires the request to be authenticated by the API server

ways that API server authenticates user request
1. static username and password file
2. static token file
3. certificates
4. LDAP server

### Static username and password file

we create a static file containing a list of username and password such as a CSV file with the following information:
```
password123,user1,001
password123,user2,002
```

then we pass this file to the API server as the source for authentication using the command line argument
**--basic-auth-file=user-details.csv**
restart the api-server

```
kubectl config set-credentials myuser \
  --username=admin \
  --password=mysecretpass
```

or in the kubeconfig file
```
users:
- name: myuser
  user:
    username: admin
    password: mysecretpass
```

### Token authentication

instead of basic username and password, we create a file containing the token and the restart the api server with the command line argument
**--token-auth-file=token-details.csv**

