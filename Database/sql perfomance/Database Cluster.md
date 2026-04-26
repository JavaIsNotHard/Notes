Database cluster : not to be confused with a collection of database server, Database cluster in the context of of Postgres means having different databases inside a single running server 

A database contains multiple database objects
a database itself is an object
a database contains the following objects inside it
- Tables
- Indexes
- Views
- Sequences
- Functions

All database objects are represented by OID (object identifiers)
the relationship between them are stored in system_catalogs

each row inside a db table also has a unique OID associated with it which is hidden from the user