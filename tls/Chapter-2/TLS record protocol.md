- This protocol provides two operations:
	- confidentiality  -> defines a shared secret 
	- message integrty -> the shared secret key is used to form a MAC 

![[Screenshot 2024-11-17 at 16.51.17.png]]
- The application layer message is fragmented into blocks of 2^14 bytes (16384) or less. 
- Next compression is applied and the compression must be lossless and may not increaes the length of the fragment by more than 1024 bytes. TLSv2 does not have a compression schema defined so no compression is done. 
- MAC is generated using the following formula

![[Screenshot 2024-11-17 at 16.54.27.png]]

- The MAC (message plus the hash) is then encrypted with one of the following options
![[Screenshot 2024-11-17 at 16.56.18.png]]

- The last step is to prepend a header of the following fields 
	- content-type: the higher level protocol used to process the enclosed fragment (change ciper spec, alert, handshake, application data)
	- Major version: major version used by TLS 
	- minor version: minor version used by TLS
	- compressed length

