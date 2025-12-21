sql statement -> validates -> optimizes -> execution plan -> execute the plan on behalf of the client

 - check that the query is correctly specified
- resolve names and references
- convert the query into the internal format used by the optimizer
- verify that the user is authorized to execute the query

1. parser:
	canonicalizes tables into fully qualified names of the form `server.database.schema.table`

2. catalog manager:
check that the table is registered in the system catalog
The system catalog stores **metadata**

3. authority checking

