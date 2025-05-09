the guarantees of eventual consistency is not sufficient for some applications
it is because eventual consistency doesn't guarantee that an operation has a happened-before relationship i.e the effect of an operation can happen before the because of the lack of ordering guarantee from this consistency model 

casually related operation are those that has the happened before relationship

strong consistency guarantees the happened-before order among operations
but we don't need to reach for strong consistency as well since we can use a weaker consistency model called casual consistency
this model is weaker than strong consistency but stronger than eventual consistency

Causal consistency model captures the notion that casually-related operations should appear in the same order on all process
but the processes or replicas may disagree on the order of casually independent operations

using casual consistency to build a replicated data store using COPS (clusters of order-preserving servers) which are a key-value store that delivers casual consistency across geographically distributed clusters
in COPS, a cluster is setup as a strongly consistent partitioned data store

COPS provide low latency by directing client requests to their local data center and ensuring that these requests can proceed without waiting for or talking to other data centers
COPS offers casual+ consistency which is a combination of casual consistency and convergent conflict handling

casual consistency does not provide any order for concurrency operation since they do not have the happens before relationship in their operation order
two unrelated concurrency operation put(x = 1) and put (y = 2) can be executed in any order 
but if the operations are related, example, they put to the same key then we have a conflict and this is we do not want conflicts because they cause divergence in the system 
convergent conflict handler is used to deal with this conflict which requires a handler function f, commonly used handler function is the last-writer-wins rule

In COPS, any replica can accept read and write requests
client sends its request to its nearest replica called the local replica
when client sends a read request to its local replica, the the latter replies with the most recent value available locally
the client on receiving the response, will add the version (logical timestamp) of the value it received to a local key-version dictionary used to keep track of dependencies

the dependency table is used to track the order of operation for a version number

when a client sends a write request to its local replica, it adds a copy of the dependency dictionary to the request
the replica then assigns a version to the write, applies the changes locally and sends an acknowledgment back to the client with the version assigned to it

it can apply changes locally, even if other clients updated the key in the meantime because values are represented using LWW registers meaning that the local replica doesn't have to wait and see if other replicas has written a new value to the same key

when a replica receives a replication message, it doesn't apply it locally immediately 
it checks if it has committed the dependencies for the newest write in its local replica
if it does not have the required writes that is in the dependency of the newest write request then it waits until the required version appears
if all the dependencies have been applied locally then it also applies the newest changes locally

the replica could fail after committing an update locally but before broadcasting it, result in a data loss
this tradeoff is considered acceptable to avoid paying the price of waiting for one or more long-distance requests to remote replicas before acknowledging a client write
