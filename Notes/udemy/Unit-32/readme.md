# Schema VS Data migration

Schema migration is about adding columns, removing columns, adding tables, removing tables and so on. 
Data migration is changing the data or moving the data from one column to another.

There are 2 ways to do schema and data migration
- Doing both schema and data migration in the same migration file
- Creating separate migration file for separate operation

For example, we create a post table in our database which holds the longitude and latitude values but now we want to create a new schema having column location of type point which will hold point the longitude and latitude for us. We also want to drop both the longitude and latitude column from the table.

# Doing both schema and data migration in the same migration file 
suppose the migration file has the layout something like this
`create location table -> complete -> copy all the lng/lat into location table -> takes time but is completed as well -> drop table lng/lat`
Now we also assume that we cannot have a down time in our application. We have a server listening to request from users about the lng/lat in our original schema. Then we apply the entire migration at the same time

## Doing schema and data migration in different steps
We make some changes in our schema migration file to change the schema structure of our database -> Then we make changes in our server based on the changes on the schema -> Then we can perform some data migration -> Change the server code respectively -> Repeat these steps


