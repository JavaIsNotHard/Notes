there are two types of DNS message
- query message
- response message

the first 12 bytes are the header section, which includes the following fields
- identification - 16 bit -> used to match the response message with the query message
- the flag bit which is used to indicate whether the message is a query or a reply, another bit to specify whether it is an authoritative server for the query or not, a 1 bit recursion when the client desires recursion for further query processing and more
- 