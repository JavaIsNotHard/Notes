The main idea of this architecture is that we have a *always on* **host** which services request from other hosts end systems called the **clients**. 
In this architecture, the clients to not communicate with each other directly.
The **host** or the **server** has a fixed known address, also known as the [[IP address]].
One of the major architectural problem that client-server architecture faces is [[scalability]]. A single server cannot withstand the incoming request from a lot of hosts at a time. So to solve this problem a large cluster of hosts are used commonly referred to as [[data centers]]. 
Client-server architecture are [[infrastructure intensive]]