
we assume that our DBMS is a "disk oriented" architecture which means data are stored on non-volatile disks

the job of the DBMS is to manage the movement of data from disk to memory and vice versa

before that, we need to understand the storage hierarchy:

1. CPU registers
2. CPU caches
3. DRAM
4. SSD
5. Hard disk
6. Network storage

as we go down the hierarchy, the components before cheaper and storage capacity becomes larger but the latency increases at the same rate

latency numbers to know
1. CPU registers : 1 ns (in human time: 1 sec)
2. CPU cache: 4 ns (in human time: 4 sec)
3. DRAM: 100 ns (in human time: 100 sec)
4. SSD: 16000 ns (in human time: 4.4 hours)
5. HDD : 2000000 ns (in human time: 3.3 weeks)
6. Network storage: 50000000 ns (in human time: 1.5 years)


Sequential access vs random acess

in non-volatile storage, random access is always going to be slower than sequential access since we need to jump between blocks and sectors to randomly access data that are stored far from each other

the job of the DBMS is to maximize sequential access as much as possible


## System design goal

design a DBMS system such that it is allowed to manage a database whose size exceeds the total amount of memory of the system i.e we allow a database whose size is 100GB even though the size of the memory is only 16GB

reading/writing to disk is expensive, so we need to make sure we avoid them as much as possible

maximize sequential access over random access