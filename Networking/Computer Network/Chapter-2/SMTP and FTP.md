SMTP stands for simple mail transfer protocol which is a push protocol that is used to push mail from one server to another server mainly a main server. A client interacts with a mail client in their host computer and the mail client interacts with the mail server of the host. The main server resides separately from the mail client and is always on. Before transferring data (mail), the sending host will create a TCP connection with the receiving host and then perform an application layer handshaking (not the same as three way handshaking TCP performs). This handshaking method has the following commands:
1. HELO
2. MAIL FROM
3. MAIL TO 
4. DATA
5. QUIT
Once the handshake is complete then the sender host will compose a mail according to the mail message format specified by the SMTP protocol. 
The host's mail server then pushes this mail into the receipts mail server if they are active if not then they retry this operation for 30 minutes until they give up. 
Mail messages are always to be encoded in 7 bit ASCII characters which is one of the down side of the SMTP protocol because modern computers use 128 bit unicode characters. 
TCP connection by the sending side is established with the recipient host at port 25

The problem with SMTP is that it is only a push protocol i.e this cannot be used to pull mail that reside in the mail server. The recipient will have their mail in their mail server and to view that mail they are using their mail client as a frontend. Since SMT is a push protocol we need another protocol to be able to pull the mail out of the mail server for the host to view through the mail client. This can be done using POP3 or IMAP or web based mail clients 
POP3 is similar than IMAP

## POP3
doesn't maintain the user state
the mail client established a TCP connection with the mail server at port 110
There are 3 phases in POP3 which includes authorization, transaction and update. The authorization phase is when the host enters their username and password, the transaction phase is when the user retrieves mail from the mail server using various POP3 commands. The update phase is when QUIT command is applied and the connection is closed. 
POP3 has 2 modes of operation
- read and delete -> the mail read from one host computer cannot be read from another host computer because the mail are deleted
- read and keep -> the mail after reading is not deleted which makes it easier for host to view the mail from more than one mail clients 

## IMAP
POP3 doesn't let users to create folders in the mail server, whereas IMAP makes user able to create folders and manage them in the mail server. 
IMAP maintains the user state. 


## FTP
file transfer protocol
similar to http where they both are a transfer protocol but have many important differences. Mainly FTP uses out of band connection meaning that control connection and data connection are separate from one another and needs 2 or more sockets to transfer a file. A control connection is established at port 21 and using this connection the user can send various control information such as username, password and more. The data connection is only used to transfer the file from one server to another server
A FTP interface is used to connect to the FTP server to access files from the local machine 
For each file transfer a new TCP connection is established 
FTP maintains user state information and associates a connection to a FTP account. Monitors the directory tree that the host traverses and the files they transfer and many more. 
