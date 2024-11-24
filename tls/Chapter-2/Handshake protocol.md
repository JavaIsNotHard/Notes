![[Screenshot 2024-11-17 at 17.06.22.png]]

- the type field indicates on of 10 messages
![[Screenshot 2024-11-17 at 17.07.03.png]]

- Length: the length of the message in bytes
- Content: the parameters associated with this message.

![[Screenshot 2024-11-17 at 17.18.29.png]]

## Phase 1 : Establish the security parameter
- client sends a client_hello message to the server with the following parameters
- version: the highest TLS version understood by the client 
- random: a combination of 32 bit timestamp and 28 byte randomly generated number. 
- session ID: non zero value indicates either a new connection in an existing session or to update the parameters of an existing session. A zero value indicates that the client wishes to establish a new connection in a new session.
- cipher suite: list of cryptographic algorithms supported by the client.
- compression methods

- the client waits for the server to send a server_hello message which contains all the parameters as the client:
	- version: the lowerst version suggested by the client and the highest supported by the server.
	- random: random number that is different from the random number sent by the client
	- session_id: if the value is nonzero the same value is used otherwise a new value is generated as a session id 
	- cipher suite contains a single cipher selected by the server from the proposed fields by the client.