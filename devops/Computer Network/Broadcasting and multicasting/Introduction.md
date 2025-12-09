broadcast -> sending message to all possible receivers in the network 
multicast -> sending message to only those receivers that are interested in the message

ipv4 supports both broadcasting and multicasting but ipv6 only supports multicasting and generally these broadcast and multicast messages are sent through a UDP packet

TCP cannot be used because it is a connection oriented protocol and only one host can send message to another host at a time using TCP

of a MAC address, if the lower order bit of the higher order byte is turned on then it is a multicast address. example, 
00:12:AB:12:22:34 -> here the higher order byte -> 00000000  and the lower order bit = 0 so it is a normal MAC address 
but 01:12:AB:12:22:34 -> here the higher order byte -> 00000001 and the lower order bit = 1 so it is a multicast MAC address

each subnet has a local subnet-directed broadcast address which is formed by placing all 1 in the host portion of the MAC address
example, 
192.168.18.0/24 is the original subnet then the local subnet-directed broadcast address is
192.168.18.255 because /24 is the subnet

and 255.255.255.255 refers to local network broadcast rather then subnet-directed broadcast, which is useful only within the subnet

command to finding all the devices in the broadcast domain
`nmap -sn 192.168.18.0/24`



