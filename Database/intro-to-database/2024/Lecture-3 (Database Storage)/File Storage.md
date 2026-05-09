databases typically stores data on files typically one or more files

the OS treats this files as normal files whereas the database engine is responsible for making the content of those files meaningful

early system also used a separate FS just to run database i.e a whole server only dedicated to run database servers and an FS that is optimized for running database operation

each DBMS writes content of the files on their own format which means that a MySQL file cannot be read by a Postgres server and vice versa


[[Storage Manager]]
