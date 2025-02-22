- frangipani server 
- petal - virtual disk server 
- caching disk blocks in local frangipani server 
- write back caching - any modification done to non-shared files that persistent in remote petal server can be cached in local memory 
- each server is decentralized with one another

challenges with frangipani (mainly caching and decentralization)
- cache coherence 
- atomicity
- crash recovery

- we need consistency view of data between workstations or client applications that use the frangipani server 
- if one workstation modifies data in its local memory then that modification must also be visible in another workstation 
- this problem where modification in one local memory or local cache is not visible in another is called cache coherence

- this can be solved by using the cache coherence protocol