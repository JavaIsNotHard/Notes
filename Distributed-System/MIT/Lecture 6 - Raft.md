
MIT lecture notes 
- test and set server which basically chooses one of the backup server as the primary when the primary server is down 
- this server is responsible to choose who is going to be primary 
- this test and set server has a single point of failure 
- the decision of who should be the primary is critical because it can cause split brain 

- when a single client communicates with multiple test and set servers and the rule requires the client to get data from both the servers in order for the result to be valid then this approach has a flaw of not being fault tolerant because even if one of the test and set server is down then the whole system is considered down
- another approach is to only get result from a single test and set server and assume the others to be dead or crashed. This approach also has a problem, if the other server is not crashed i.e it is still alive and accepting request but because of network partition the other client couldn't communicate with the second server. Now clients are now no longer in sync with each other and this is the split brain problem. Two or more servers, for the same record has different data.
- For example if two VMs in the VMware-FT approach communicated with two test and set server then suppose there is a split brain, this means that both the VMs can be considered as primary because they cannot communicate with each other
- this happens because computers cannot distinguish between a server crash and a network partition

How to build replication system that does not suffer from split brain 
- use network connection that cannot break 
- majority vote rule 

Majority vote rule
- use odd number of servers for one half to have a majority votes 
- for any operations to be performed, a majority of the server should be  i.e more than half 


if you need majority of server to proceed and you go through a succession of operation and for each operation someone assembled a majority, like votes for leader then at every step the majority assembled for that step must contain at least one server that was in the previous majority i.e any two majority overlap in at least one server 

this property is what raft is relying on to avoid split brain 




Raft whitepaper 

Consensus algorithm 
- allow group of machines to act as a coherent group where the group acts as if it were a single machine 
- take collection of unreliable machine and make them reliable 

- consensus algorithm are used in the context of replicated state machine 
- state machines on a collection of servers compute identical copies of the same state and can continue operating even if some of the servers are down

- replicated state machines are implemented using replicated logs 
- each server stores its own local copy of the log, the log contains a series of commands which the state machine executes in order 
- this makes each state machine execute same command in the same order 

- keeping the replicated state machine consistent is the job of the consensus algorithm 


how does Raft provide consensus?
- leader election
- log replication
- safety


job of a leader in consensus 
- accepts log entires from client and replicate them on other server
- tell servers when it is safe to replicate the log in their own machine 


basic design of raft 
- contains a cluster of 5 servers where we can tolerate two failures 
- the server is in 3 state: 
	- leader : handles all client request
	- candidate : used to elect a new leader
	- follower : they issue no request on their own but respond to request from the leader
- raft divides time into terms of arbitrary length 
- each term begins with an election in which one ore more candidate attempts to become a leader followed by the normal leader or follower operations
- if a candidate wins the election then it serves as a leader for the rest of its term 
- in case of split vote, another election is held until a leader is elected 

- terms in raft are monotonically incrementing counter 
- each server stores the current term number
- the term number are exchanged whenever the servers communicate 
- a server with smaller term number will update its term number to a larger value during the exchange
- if a candidate or leader detects a stale local term number then it reverts back to follower state 

- servers communicate using RPCs 
- during election, candidates send RequestVote RPC 

Leader election 
- every server starts up as followers 
- the server remain as followers until it receives valid RPC from candidate or leader server (AppendEntries RPC that carry no msg)
- leaders send heartbeat messages to all other servers to maintain its authority 
- if a follower does not receive a heratbeat msg over a extended period of time then it assumes that the leader is dead or the term is over (this is called election timeout) and begins a new election to choose a new leader

- first the follower increments its current term number 
- it votes for itself and sends VoteRequest RPC to all other servers in parallel 
- the follower remains in this state until one of the following 3 things happen:
	- it wins the election
		- a candidate wins an election only if it receives majority vote from servers in the cluster 
		- each server will vote for at most one candidate on a first come first serve basis 
		- the majority vote rules makes sure that at most one candidate becomes leader 
		- the new leader sends heartbeat messages to all servers to establish authority and prevent new election
	- another server wins the election
		- while in candidate state, the server may receive AppendEntires RPC from other server claiming to be leader
		- if the leader's current term is at least as large as the candidate's term then the candidate recognizes the leader as legitimate and returns as follower
		- if the claiming leader has a term number less then the candidates' then the candidate ignores the msg 
	- a period of time goes by without any leader 
		-  if multiple servers become candidate then the votes are split and no server gets majority vote (called split vote)
		- in this case a new election takes place 
		- without extra care split votes could repeat indefinitely 
- to prevent split vote a random election timeout is chosen 

Log replication
- happens after the leader is elected, the new leader starts serving client request 
- client sends a command which is to be executed in the replicated state machine 
- first the command is not execute but rather appended to its log 
- then it issues AppendEntries RPC to all followers in parallel and once it knowns that all the followers have the command in their entry then it starts to applies the entry to its state machine and returns the result to the client 

- each log contains the term number in which the log was appended at 
- the actual command to be executed by the state machine 

- the leader decides when it is safe to apply a log entry to the state machine
- such entry is called committed 
- the log entry is committed if the leader replicates it to majority (using majority vote rule) of the server 
- the leader keeps track of the highest index number of the log entry in its local log entires 
- this index number is send to other followers and it commits all the logs up to the highest index number provided by the leader since they are guaranteed to be safe by the leader 

Log matching property of Raft:
- this property ensures consistency between logs in different servers 
- the properties include
	- if two entires in different logs have the same index and the same term then they store the same command
	- if two entires in different logs have the same index and the same term then logs are identical in all preceding entires 

Raft keeps track of committed entries using the commit index 

each server keeps track of its own commit index 
the follower relies on the leader to update their commit index 
the leader determines which entries are safe to commit 
if an entry has been replicated to majority of the servers then that entry is said to be safe to commit 
leader sends period AppendEntry RPC (heartbeat msg) to the follower alongside its commit index
based on the commit index, the followers can execute their logs in the order they arrived and be consistent with the leader

there are cases where leader crash leaves the logs in inconsistent state 
raft removes this inconsistency by forcing the followers to replicate the leader's log 
for this the leader needs to find the log entry index where both the leader and the follower agree upon i.e they contain the same term number and the same index 
upon arrival to that entry, all the logs after that are deleted and are replicated by the leader's log 
the leader keeps track of something called as **nextIndex** for each follower which is the index of the next log entry that the leader send to the follower
when a new leader is elected then the nextIndex is set to the index number after the current index of the leader's log 
the leader checks for inconsistency using AppendEntry RPC (this RPC contains the leaders current index and term number)
if the leader's current log and the followers log do not match then the follower sends a rejection and the follower's nextIndex is decremented 
this process continues until the logs are equal at which point the leader will remove all conflicting entries and append the leader's log 


## Fast backup in raft
- instead of going through the followers' and the leaders' log one by one, the algorithm can use the fast backup method 
- for this, the followers' needs to include additional information about its state during the AppendEntry response back to the leader 
- the info includes:
	- conflict term : the term of the last matching entry
	- first index in conflict term : the earliest index where the follower conflicts with the leader 
- for example we have the following logs between the follower and the leader
	- leader `[1:1, 2:1, 3:1, 4:2, 5:2, **6:3**, 7:3, 8:3, 9:3, 10:3]`
	- follower `[1:1, 2:1, 3:1, 4:2, 5:2, **6:2**, 7:2, 8:2]`
	- here the conflict term -> 2 (because this is the term of the last matching entry between the leader and the follower)
	- here the first index in conflict term -> 6 (because this is the earliest index where the follower conflicts with the leader)
- the leader then searches its own log for the latest index with conflict term = 2
- then it sets the inconsistent follower's nextIndex = 5 + 1 = 6
- the leader then removes all the entries from starting from index 6 and append its own entries starting from index 6 


Safety in Raft:
mechanisms to ensure that each state machine executes exactly the same command in the same order
the restrictions that raft applies makes sure that the leader for any given term contains all of the entries committed in the previous term 

Election Restriction 
- in some consensus algorithm such as ViewStamped Replication, a new leader can be elected even if it doesn't contain all the committed entires 
- Raft makes a guarantee that all the entires committed from the previous term are present on the new leader from the moment of its election
- this is done during the voting process by making sure the candidate cannot win unless it contains all the committed entires 
- when candidate sends its RequestVote RPC then it also contains the term of the candidate's last log entry and index as well 
- the voter's compare their index and term with the candidates and check if the candidates values are equal or less than the voters
- if the values are equal then the can cast their vote for the candidate 
- if the values are less then it will not cast its vote for the candidate
- committed entries are present on at least majority of the server as per the majority rule 
- if those majority servers all vote for the same candidate then that candidate wins the election and becomes elected as the new leader


## Committing entries from previous terms 
- the leader knowns that an entry from its current term is committed once that entry is stored on a majority of the server 
- if the leader crashes before committing the entry then future leader will try to finish replicating the entry
- just because the entry is stored in majority of the server, doesn't mean that it is committed 