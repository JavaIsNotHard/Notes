contains the following four tuples 
(Name, Value, Type, TTL)

based on the Type we determine what Name and Value is
for example, if Type = A then Name = hostname and Value = IP address for the hostname
basically providing a standard hostname to IP address translation
example (foo.bar.com 171.2.12.1, A) is a type A record

Type = NS then Name = domain name that we are trying to query and Value = hostname of the authoritative DNS server that knows how to get the address of our domain name
example (foo.com, example.foo.com, NS)



here are the steps to add our dns record into the global nameserver database

we need a registrar which is certified by the ICNAA such that it can add domain names for TLDs as well as root 
