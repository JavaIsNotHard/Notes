a database cluster = folder created during the `initdb` step during PostgreSQL intialization
mostly it points to the folder `/var/lib/postgresql/16/main`

a database = subfolder inside the base folder 

files and indexes = files inside the subfolder inside the base folder

files and indexes whose size is less than 1GB are stored in the same file

`relfilenode` : a separate file that points to the actual file on disk where the table's data or index's data lives

getting the database object information from the system_catalog

```sql
select oid, datname from pg_database where datname = current_database();
```

to get the relfilenode of a table which is different from the OID then we use the following query

```sql
SELECT oid, relname, relfilenode FROM pg_class WHERE relname = 'your_table';
```

the relfilenode value changes by issuing one of the following commands:
TRUNCATE, REINDEX and CLUSTER

each table file has two associated file suffixed with __fsm and __vm 
fsm suffixed file = free space map
vm suffixed file = visibility map

these are only for heap file tables not index files

when we create a new DB inside postgres, it creates a new OID asscoiated with it and a new folder inside the base folder, but the suprising thing is the new folder  already consists of multiples files inside, it is because **copies a template database** called `template1`
They contain the default system objects that every PostgreSQL database needs to function — things like:

- built-in data types
- built-in functions
- system catalog tables (like `pg_class`, `pg_attribute`, etc.)