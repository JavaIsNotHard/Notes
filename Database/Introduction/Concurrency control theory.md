## Motivation 

### Race condition: (concurrency control)
suppose we have two identical queries which updates the same data on the same page but with different values, then what should be the final data block. 

### Durability: (Database recovery)
Suppose one account transfer 100$ to another account and suppose between the transfer and before the end of the transfer a power loss occurs. What would be the final state of the database.


Concurrency control and durability are one of the most important feature of a database system 
Avoid implementing concurrency control and recovery system by ourselves because they are hard to implement are you are probably going to get it wrong. 
The selling point of your application is not the recovery system or the concurrency control of your application but that is not the differentiating aspect of your application with your competitors 

## Transactions 
To make sure everything is running properly and consistently we need to understand transactions. Transactions guarantees ACID properties. 

### What a Transaction is?
Sequence of one or more operation on a database to perform some higher level functions. 
These operations include stuffs like: 
SQL queries to read and write stuff, update stuff and delete stuff 

The higher level function means some feature that we want our application to performs. For example, transferring money from account A to account B. This feature is not available to us using the database but we perform this operation using many reads and writes given by the database system itself 

Basic unit of change in a DBMS. So whether it is a single query or mutliple query it is always going to be a transaction. 
We are not going to allow parital transactions, if we have sequence of 5 operations to do then we want all 5 to complete or we want none of happen. Even if we are using a single query such as update which updates 5 items in a tuple, then in the world of transaction either all the data items in the tuples are going to be updated or none of the data items are going to be updated. 

## Strawman System 
Database system that only supports a single thread, only one transaction or one query can run at a time. If multiple queries come to the system at once then they are placed in a queue and the sytsem is going to remove items from the queue one after another and perform that query 
Before transaction starting executing, it copies the entire database and make all the changes to the copy of the database and if it succeed then we flip a pointer to say that the new version of the database is the new file we just created. 
So if suppose out of 5 queries only 3 succeed and the system crashes then we still have our original database file and everything is correct in that file. 

### Will this work?
Yes 
### Is this system fast?
No. This is going to work if the data file is only few megabytes but suppose our data file is petabytes is size then copying the file to a new file to going to take a long time.
This is also running in a single thread. If a data item is not in memory then we have to stall our database thread, perform an I/O which is expensive and then resume our database thread again. 

## Better appraoch
Allow transaction to run simultanously and interleave their operations to maximize our parallelism but still get all the safety guarantees that we want and all the correctness that we want. 

### Why do we need this?
- better throughput and utilization of hardware resources 
- Increased response time. the system is going to look and feel snappier 

### We would also like
- correctness 
- fairness 

**Transactions are hard to implement**


## What we want 
1. interleaving of operations, this can lead to many problems like:
	- Temporary inconsistency  (ok, unavoidable)
	- Permanent inconsistency (bad)
	Temporary inconsistency is ok because our transactions are composed of many operations and each operations change the state of the database which means because all the operations are done, we can temporaryily have an inconsistent state but once all the opeartions are done we should have a concistent state. 


A DBMS is concerned only with the reads and writes inside the database system 
Anything that happens outside the database system inside a transction cannot be reverted or rolled back by the system.
This outside operations could be something like sending a notification right after starting a transaction stating that your changes have been made successfully but suppose the transaction failed midway then we do not have any way to revert the notification back.
We can only revert changes to the database.. 


## Transactions in SQL 
We start a new transaction using the **BEGIN** keyword 
We then perform all the operations that we want inside the **BEGIN** statement. Once our operations are complete then we want to either **COMMIT** or **ROLLBACK**. 
- if **COMMIT** then the DBMS will save the changes to the disk otherwise if there were any error of inconsistency or crash or something then we would **ROLLBACK** or **ABORT**. 


## The correctness criteries: ACID 
Atomicity -> no partial transactions 
Consistency -> if the transaction is consistent and if the database before the transaction was consistent then the outcome should be consistent as well 
Isolation -> There will be multiple transaction running at once but it works as if a single transaction were only running 
Durability -> persist the changes permanently on the disk 


### Atomicity of transaction 
two scenarios: 
1. **If A transfer money but the transaction is aborted by the database**
2. **If A transfer money but power loss occurs** 
In both of these scenarios what should happen to the final state of the database 

#### Mechanisms for ensuring atomicity 
1. **Logging** 
2. **Shadow paging** 

#### Consistency 
- database consistency 
- transaction consistency 
#### Isolation 
Running each transaction as if they were the only transaction running in the system 
- involves concurrency control 
- has to let multiple transaction to run at the same time 
Mechanisms of concurrency control invovles: 
- Pessimistic concurrency control  -> Don't let a problem arise beforehand
- Optimistic concurrency control  -> Assume conflicts and errors are rare so we postpone the error checking before we commit 

When running two or more transaction at the same time we not know the order of the execution of the transaction. So we must guarantee that the order that the transaction runs should result in a serial order (which is running the second transaction only after the first transaction has been complete)

The order in which a transaction runs in called a **Schedule**
and how do we judge the correctness of the **Schedule** i.e the schedule is equivalent to a serial schedule. 

Formal Properties of Schedule 
- Serial Schedule  -> there is not interleaving of transactions 
- Equivalent Schedule  -> if two transaction schedule has the same end state then they are called equivalent 
- Serializable schedule -> if a schedule is equivalent to a serial schedule 

What are the conflicts that could violate the serializable of a transaction 
Two operations are said to be in conflict if 