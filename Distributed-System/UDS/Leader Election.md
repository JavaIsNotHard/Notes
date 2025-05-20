	a leader election algorithm needs to guarantee that there is a most one leader at any time and that an election eventually completes even in the presence of failure


## Raft election algorithm
each process is in one of three states
1. the follower state, where the process recognizes another one as the leader
2. the candidate state, where process starts a new election proposing itself as a leader
3. the leader state, where the process it the leader

time is divided into terms, where there are different phases like 
1. leader election
2. normal operation, leader accepts client request, appends log entries and sends heartbeats
3. failure detection

each term is numbered with consecutive incrementing integers
each term begins with a new election during which one ore more process attempts to become leader 
what triggers a leader election?

timeouts that occurs when the leader doesn't send heartbeat messages within a time frame or the leader sends a term number less than the candidate term number
a leader sends periodic heartbeat to all its followers
when a timeout occurs when the follower that detected the timeout starts a new election by incrementing its term number and transitions its candidate state


## Practical considerations
instead of implementing a leader election from scratch we can use any fault-tolerant key-value store that offers a linearizable compare-and-swap operation with a expiration TTL

the compare and swap operation will compare the current value with our old value and check if there are other processes that are updating the value, if there are other processes then it is blocked else if the value is the same then it gets updated to the new value and acquires the lease

the expiration time defines the time to live for a key after which the key expires and then they are removed from the store
each competing process will try to acquire the lease by creating a new entry in the store, the first process to create an entry will become the leader
the expiration time can be extended if the leader wants to update more data in the store

example why lease are not enough to avoid race conditions in distributed systems or a monolithic system
suppose there are multiple process writing to the local file system, the first process to write to the FS gets the lease and continues 
but the problem is that the OS might preempt the process that holds the lease until the expiration time hits and the process no longer holds the lease
once the process resumes, it still thinks that it has the lease and writes data to the FS leading to inconsistency and race condition

a solution to this problem could be for the process to check its local time before performing any operation, compare it with the lease expiration time, abort the write if the local time pasts the expiration time 

this is assuming that clocks are synchronized but clocks aren't perfectly accurate

assign a version number to each file that is incremented every time the file is updated
the process holding the lease can then read the file as well as its version number, do some computing and update the file conditionally using compare and swap operation where the process compares the version number it saw with the current number, if the version number changes then it aborts the operation if the version number are the same then it can proceed to write to the FS
