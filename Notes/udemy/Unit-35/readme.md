# Security Around Postgres 
- We never take user input directly and run them directly inside the query that we provide. The user input could be user trying to enter their email and password to login and so on. This is also known as SQL injection where users can run arbitrary queries inside the database even if they do not have any permission to do so.
- Remedies for SQL injection
	1. Using prepared statement which prepares our query to take in values for the placeholder that we have added into our query. Then once it gets the value it executes the query by replacing the value with the placeholder.