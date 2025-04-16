## physical clock 
based on a vibrating quartz crystal, not accurate and can caused clock drift based on the difference in manufactuerers and external temperatures

the synchronization can be implemented with a protocol called the network time protocol
client estimates the [[clock skew]]  by receiving a timestamp from a NTP server and correcting it with the estimated network latency
this causes the clock to jump forward or backward in time which creates problems when comparing timestamps

we cannot depend on the wall time clock for ordering operations across nodes
two operations can't run concurrently in a single thread process as one must happen before the order creating a casual ***happens before*** relationship between the processes
this is because the operation that happened first can have side-effects that affect the operation that comes after it

## logical clock 
a counter, incremented before an operation is executed 
if two operation execute on the same process then on emust come before the other based on the logical timestamp
but what if they are running on different processes 

example, suppose you are sending a email to your friend. 
any action that you take before sending the mail must have happened before the action that your friend took after receiving the mail 
when on e process sends a message to another, it creates a synchronization point

the idea is based on [[lamport clock]]
![[Screenshot 2025-04-10 at 8.44.48 AM.png|600]]

according to this figure, 
operation D happens before operation F hence the timestamp also reflect this dependency
but two unrelated operations can have the same logical timestamp suppose operation A and operation E have the timestamp 1
strict total ordering can be implemented by arbitrarily ordering the processes, example, is use use process ID instead of a incrementing counter

a better approach is to use vector clock


## Vector clock
each process has a local vector clock implemented with an array of three counters 
`[C1, C2, C3]` 
where C1 = counter for process 1
	      C2 = counter for process 2
	      C3 = counter for process 3

the vector clock is based on the following rules
1. the array of counters is set to 0 
2. when an operation occurs, the process increments its counter in the array by 1
3. when the process sends a message, it again increments the counter in the array by 1
4. the receiving process then merges the array by comparing with a local one and taking the maximum of the two array element-wise

vector clock timestamps can be partially ordered; given two operations O1 and O2 with timestamps T1 and T2, if:
1. every counter in T1 is less than or equal to the corresponding counter at T2
2. and there is at least one counter in T1 that is strictly less than the corresponding counter in T2
then O1 happened before O2, if O1 didn't happen before O2 and O2 didn't happen before O1 then these operations are said to be concurrent

we can't use physical clocks to accurately derive the oder of events that happened on different processes
