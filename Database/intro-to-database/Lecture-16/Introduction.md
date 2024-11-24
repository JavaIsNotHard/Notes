- the concept of transaction 
- should not have partial transactions 
- txn is a sequence of one or more operations (SQL queries ) to perform a higher level function.

## Transaction example 
- Move  100$ from account A to account B 
- check that account A has 100$
- deduct 100$ from account A 
- increase 100$ from account B
- all these fall under a single transaction

## Strawman approach 
- before every txn create a new copy of the database such that all updates happen to the new copy 
- this could make sure that any crash would not result in data corruption in the main database file.
- if the txn was successful then copy the content of the new copy to the main db file 
- if the txn was not successful then delete the new copy and  do not change anything in the main db file. 
- this is not a good approach because if the size of the db file is large (1gb or more) then copying would have addition cost associated with each transaction. 
- That means the total runtime of a txn would be `time to copy the db file + time to complete all operation in the txn`.

## Design goal 
- create a concurrent txn management system such that we can run multiple txn at the same time concurrently by interleaving their point of execution to utilize the parallelism of the computer processor such that they have the safety guarantees in place as well.


## Approach for maintaining atomicity
- logging
- shadow paging

## Maintaining isolation
- helps two txn run concurrently and make sure the end state of the database is consistent.
- the concurrency control protocol of the DBMS is what decides which the proper interleaving of operations. 
- two appraochs for concurrency control 
	- pessimistic  -> Don't let a problem arise in the first place
	- optimistic -> handle the problem at the end after all the operations are compeleted.
- when two txn run at the same time we do not know the order of execution i.e which txn will run first.
- no matter the interleaving or the order of execution we want to make sure the end result is equivalent to the result that would be produced by a serial execution.

## Serializable schedule
- Those schedule that is equivalent i.e produces the same result as that of a serial execution is called serializable schedule.
- Order of execution depends on the conflict that schedule could produce and tackling those conflicts.

## Conflicting operations
- two operations are said to be in conflict if:
	- they are different transactions
	- they are on the same object and one of them is write
- types of conflict includes
	- read-write conflict(unrepeatable read)
	- write read conflict (dirty read)
	- write write conflict
	- phantom reads 
	- write-skew


## Conflict serializable
- conflict equivalent -> 
- schedule S is conflict serializable if it is conflict equivalent with a serial schedule.
- we can check if a schedule is conflict serializable by using dependency graph or precedence graph

## Consistency property of ACID 
- if the database is in consistent state before the transaction then it must be in consistent after the transaction as well. Suppose both account A and B had the sum of 1000$ each then the total sum would be 2000$. Suppose A transferred 100$ to B then the following operations would have to happen
	-  Read(A)
	- A = A - 100
	- Write(A)
	- Read(B)
	- B = B + 100
	- Write(B)
- the sum of Account A and B must be 2000$ after these set of operations. if that is true then we say that the database is in consistent state. 

- guessing whether a schedule is conflict serializable or not requires you to know beforehand all the operations that are going to happen in the transaction.
- Knowing beforehand all operations are not guaranteed by all systems hence we need a more dynamic approach whereas operations are schedules on the fly on after another such that at the end state (after all the operations are complete) we get a conflict serializable operation

- For this problem, we use locking approaches which includes:
	- basic lock
	- two phase lock
	- deadlock detection & avoidance
	- hierarchical locking
- 