## record protocol 
- TLS is implemented via this record protocol
- this provides message transportation and encryption
- it starts with a header region and a message body region
- the header region is subdivided into 3 region which includes the header type, header length and header version 
![[Screenshot 2024-11-07 at 10.41.00.png]]
![[Screenshot 2024-11-07 at 10.40.56.png]]

- Each TLS record also consists of a 64-bit sequence number which counts the number of records sent by the other side. This is not send over the network.
- the record protocol is useful for the following reasons:
	- message transport -> the record protocol holds 16kb worth of data into its buffer, data larger than 16KB are fragments and data less than 16KB are merge together to form a 16KB data.
	- Encryption and integrity checking -> For a brand new connection there are no protection enabled. Once the handshake is complete then the record layer starts to apply encrypion and integerity checking
	- The record protocol delegates all other responsibility to subprotocols. All other subprotocols are automatically secured using the same security parameters
- Four main TLS subprotocols include: handshake protocol, alert protocol, cipher spec protocol, application data protocol.

### Handshake protocol
- Sides negotiates the security parameters and performs authentication.
- different flows of handshake protocol: 
	- full handshake with server authentication
	- abbreviated handshake that resumes earlier session
	- handshake with client and server authentication
![[Screenshot 2024-11-07 at 10.48.42.png]]
- The following is the handshake protocol message which contains a message type of 1 byte, length of 3 bytes.
- The remainder of the mssage depends on the message type. 

### Full handshake
- if the client hasn't established a previous sesion with the server then a full handshake is performed to negotiated the connection parameters 
- 
- The following things happen in this step
	- exchange the capabilities and agree on connection parameters 
	- validate the presented certificate or authenticate using any means
	- agree on a shared master secret 
	- verify the handshake message hasn't been modified by third party.
- In this configuration the client is not authenticated whereas the server is.
![[Screenshot 2024-11-07 at 10.53.28.png]]

#### Client hello
- always the first message send in the full handshake exchange
- used to communicate client capabilities and preferences to the server
![[Screenshot 2024-11-07 at 10.57.41.png]]

- the protocol version indicates the latest version the client supports
- the random field contains a 32 bytes of data where 28 bytes are random and 4 bytes are generated from the skewed clock time.
- session id indicates the session id of any previous session that we are trying to resume. for a new connection the session id will be null and for a resumed session the server can look up its cache and reconstruct the previous state of the session in the server.
- cipher suites includes all the encryption algorithm that the client supports
- compression methods as the name suggests

#### ServerHello
- server communicates the selected connection parameter to the client.
![[Screenshot 2024-11-07 at 11.03.23.png]]

#### Certificate 
- after the serverhello, the server sends its certificate chain excluding the root CA certificate. 
- The public key send by the server that is used to decrypt the private key of the certificate should match the one selected in the cipher suite option. (what does this mean?)


#### Client and server finished message 
- contains a verify_data which is basically the hash of all the contents of previous handshake contents upto this point 
- it is calculated using this formula `verify_data = PRF(master_secret, finished_label, Hash(handshake_messages))`
- here master_secret is derived earlier in the handshake
- finished_label is either "client finished" or "server finished"

### Client authentication
- requires the client to send its own certificate
![[Screenshot 2024-11-07 at 14.13.10.png]]

- this is different from the previous exchange, in this the client is requested to send their cerificate as CertificateRequest from the server to the client.
- The server then verifies the client's cerificate to enable further communication
- 

### Key exchange 
- generate pre master secret which is used to construct the master secret
- the master secret is a 48 byte shared key between the client and the server (probably?)
- 