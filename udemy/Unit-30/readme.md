# Handling concurrency and reversibility using transactions 

When using database in production, we can except multiple concurrent users trying to access data from the database. Each user creates a new connection to the database.
We connect to a postgres database using something called a `connection`. So in a single instance of the database that we have, there can be more than one connection to that database and each connection can change and modify stuffs inside the database. Each connection points to the same data pool i.e the same set of data if we are not using transactions. 

## Transaction block 
We begin a transaction using the `BEGIN` keyword, just the `BEGIN` keyword. This creates a virtual workspace like thing that has all the data of the main database but in a separate environment away from the main data of the database. So when we create a transaction, we know we create a virtual workspace inside postgres that is only accessible to a single connection or to a single user per say. This means that any changes that this single user or connection makes to the database would only change the values on their database and not on the main database. 

## Uses of transactions
Transactions are useful when you either want the whole thing to change or change nothing at all. For example we have an accounts table with users A and B. If user A sends 50 $ to user B then the balance of user A should decrease by 50 and the balance of user B must increase by 50. But if for some reason the 2nd operation i.e increasing 50 didn't happen then the whole operation i.e both decreasing and increasing would not happen. This is due to the fact that: 
- Whenever the connection gets interrupted or closed unexpectedly then any changes to a transaction would rollback to the original database. 

## Merge the transaction and the original database
We can merge the changes in the transaction and the original database by using the keyword `COMMIT`. This would change the original database with the changes in the transactions. We can also rollback to the data of the original database by using the `ROLLBACK` keyword. There is last scenario that can happen when working with transactions i.e when there is an error in the query that we run. For example, if we `SELECT * FROM <table that does not exist>` then we get an error. Now postgres goes it something called as abort state where any query whether correct or incorrect would not execute. To fix this, we have to rollback to the original database.