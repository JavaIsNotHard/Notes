
`ss` and `tcpdump`

ss -> see the binding process
tcpdump -> check the request and response packets

NO SYN means the request never reached the application or the kernel because an external load balancer, firewall, security group dropped the packet beforehand

SYN but no SYN/ACK means that the request reached the kernel but couldn't continue the request since there may not be a process listening on the address and port

IF SYN -> SYN/ACK -> ACK and then packet traversal "P." and "." as well as connection close request "F." then all the request were processed normally by the kernel but if the server still returns error, then it is some application error and the network is fine

Understanding the `ss` command

local address: port -> the address and port where our process is bound to
peer address: port -> the address and port of the remote client which is connected to the local address and port
if the remote address: port = 0.0.0.0:* or `*:*` then it means no active connection in that process