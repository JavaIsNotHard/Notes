2PC (2 phase commit) protocol is a blocking protocol
if the coordinator or any of the participants is slow or not available, the transaction can't make progress

if the nature of the transaction takes a long time to execute then blocking just isn't an option

source bank -> issuing the check deducts the funds from the source account
then the check is physically transported to the other bank
destination bank -> the check is processed

here the source bank doesn't have to wait fro the destination bank to confirm that the destination has received the check and hence this is a asynchronous transaction
one downfall of this approach is that the source and the destination are in inconsistent state during the transfer of fund between them 

this is where persistent messages are used, these messages guarantee that the message will be delivered to the recipient exactly once (neither less or more) regardless of failure

## outbox pattern

let relational database and a elastic search service be two dependencies required by a single service in a microservice architecture
the service needs to update both the relational database and the search engine service whenever the user requests to add new item to it 
but if main service crashes before updating one of its dependencies (database or the search engine), the system would be left in an inconsistent state
so we need to wrap these two updates in a transaction

we could use 2PC for distributed transaction but while many relational database supports such protocol, many search engine service do not
we also do not want the search engine to block if the search service is temporarily unavailable 

we can solve this problem by sending a persistent message to the search service whenever a item is added
since most database supports ACID transactions, we can wrap the database update and appending an entry to the outbox table into a single transaction
making sure that the the outbox table is appended if transaction commits and is not appended is the transaction aborted

on the other side, we have a relay process which monitors the outbox table for any new entry in the table 
when the relay process discovers a new message, it sends the message to the destination which in our case is the search service
the replay process deletes the message from the table only when it receives acknolwedgement from the destination that the message was delivered successfully
if the relay process crashes after sending the message but before removing it from the table then it will resend the message when it restarts which causes depulication and can be avoided using idempotency (a unique identifier) key for each message

in practice, the messages are not delivered to the destination directly but rather to a message broker like kafka which is reponsible for delivering the message to one or more destinations in the same order as they were appended

## Saga
used in distributed transaction between multiple services

A saga is a distributed transaction composed of a set of local transaction and a compensating transaction used to undo the changes of the local transaction

each local transaction updates a database and publishes a message or event to trigger the next local transaction

 two types of coordination saga :
 1. choreography-based saga
 2. orchestration-baesd saga

choreography-based saga

each service listens to an event and decides what to do next
each service publishes an event that triggers local transaction in other services 

orchestration-based saga 

a transaction coordinator or a orchestrator tells that services which transaction to execute and run and stuff, basically it coordinates the execute of transaction 

as the transaction requires multiple steps to succeed, and the coordinator can fail at any time, it needs to persist the state of the transaction as it advances