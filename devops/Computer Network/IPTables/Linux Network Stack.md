every packet that the linux kernel receives or sends has to pass through the linux network stack

routing in the linux kernel is provided by the kernel's built-in functionality also known as IP forwarding 
Sending a non-zero value to `/proc/sys/net/ipv4/ip_forward` file activates packet forwarding between different network interface effectively transforming linux machine into a virtual router

the network stack has various logical stages of packet processing, various stages like PREROUTING, INPUT, OUTPUT, POSTROUTING, FORWARD

we can have a hook (basically something like a callback function) that gets executed and allows user to add packet filtering and modification logic such that if the packet passes through any of those above mentioned stage then that hook or the callback function gets executed

This is implemented by netfilter, the netfilter's code resides inside of the Linux kernel and adds all those extension points (_i.e. hooks_) to different stages of the network stack

Iptables are user space frontend tools that helps us configure the netfilter hooks

in iptable world, PREROUTING, INPUT, OUTPUT, POSTROUTING, FORWARD are called chains because they basically set of rules that packets are tested against, one by one in order 

packets pass through this chain based on its origin and destination
callbacks added to these chains are also executed in order, a simple iptable rule can be something like 
`iptables -A INPUT -s 46.36.222.157 -j DROP`
this rule drop all the packets originating from source 46.36.222.157 before reaching the user process
a more complex example would be
```
iptables -A INPUT -p tcp -m multiport --dports 80,443 \ -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT 
iptables -A OUTPUT -p tcp -m multiport --dports 80,443 \ -m conntrack --ctstate ESTABLISHED -j ACCEPT
```

this allows both incoming and outgoing http and https packets

If the **target is terminating** (e.g., `ACCEPT`, `DROP`, `REJECT`), processing **stops immediately**
If the **target is not terminating** (e.g., `LOG`, `CONTINUE`, `RETURN`, or a jump to a user-defined chain), it **keeps processing** the next rule
If the packet reaches the **end of the chain without being accepted or dropped**, the **default policy** for the chain is applied (e.g., `ACCEPT` or `DROP`)

policy is basically a default action when none of the rules match and the packet reaches the end of the chain. policies are terminating target which means after the packet reaches the default policy then it terminates

