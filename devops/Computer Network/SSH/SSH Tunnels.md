using ssh's encrypted connection between two hosts to securely transport other network traffic

we instruct ssh to listen on a port at one endpoint, encrypt any traffic sent to that port, transport it through the tunnel, decrypt it at the other endpoint and forward it to the final destination

### Local port forwarding
forward my local port to a remote destination via the SSH server

`ssh -L [local_port]:[destination_host]:[destination_port] user@ssh_server`

Listen on my local port 8080 and forward any traffic through user@ssh-sever to the destination host and port

suppose we have the following port forwarding logic
`ssh -L 8080:database.internal:5432 user@bastion.company.com`

now we can connect using the command:
`psql -h localhost -p 8080 -U dbuser`

this forwards the traffic at port 8080 of localhost to 5432 of the server


### Remote port fowarding

1. step 1 : TCP handshake (you -> server)
2. step 2 : ssh protocol negotiation
3. step 3 : remote forward request
	- ssh client sends a request to the server which tells the server to listen on a particular port number
4. step 4 : sever processes request 
	- decrypts the ssh message protocol
	- reads the request to bind the server to a port number
	- creates a new listening socket on that port number
5. step 5 : server confirms the request has been confirmed back to the client

now remote user can connect at `remote_addr:<port_number>`


