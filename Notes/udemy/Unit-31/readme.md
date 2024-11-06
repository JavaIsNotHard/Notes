# Managing Database Design With Schema Migration

Things to know before doing migration: 
- Running a database migration and changing the api server code to match the database migration should be done in the same exact time. This can be achieved by first deploying the server code with the necessary changes then once the deployment completes, immediately execute the migration files such that the migration are applied. This is because deploying the server code takes some time to complete whereas running a migration file is done in a moment. 
- When doing a code review request we should first create the new version of the api server code and then create the migration file matching the operation of the server code. So when reviewing the next person could migrate to the new database schema as well as the server code, evaluate the code and once the review is done revert back to the previous version of the schema and server code. 

## Creating migration files 
There are various programming language frameworks available to us to create migration files. We could create a migration file by using raw sql or using the builtin language specific functions and keywords. 
For example in django, when we make changes in our schema design we run the make migration command to create a migration file of the current changes that we made in the model. Then we could apply the migration or not apply a migration later on. 

A migration file mainly has two parts i.e the upgrade part and the downgrade part. The upgrade part is the new sql that creates changes in our pre-existing schema. The downgrade part is reverting back to the previous version of the schema.
There are various levels of migration that we can apply and revert back to. Reverting back to a previous version of the schema makes it flexible enough to write a new migration file i.e add new features that the previous upgrade didn't have. 


## To rename a column we use the query
```sql
ALTER TABLE <name of table> 
RENAME COLUMN <name of column> TO <new name>;
```