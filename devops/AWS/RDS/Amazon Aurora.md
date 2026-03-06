proprietary technology of AWS 
gives us a DB driver that simulates how MySQL or how PostgreSQL works

it is cloud optimized and gives 5x the performance of MySQL and 3x the performance of PostgreSQL

it is not a MySQL or PostgreSQL instance running, its completely different in the backend, the only similarities we can find is the interface clients interact with

**Aurora is _not_ running stock MySQL or PostgreSQL end-to-end.**  
It _exposes_ the MySQL/Postgres **wire protocol + SQL semantics**, but the **storage, replication, logging, and recovery layers are completely different**.

basically the storage layer is completely different from MySQL and PostgreSQL

## When SHOULD you use Aurora?

✅ Use Aurora if:
- You need **high availability**
- You want **fast failover**
- You have **read-heavy traffic**
- You’re already on MySQL/Postgres
- You don’t want to manage replication

## When NOT to use Aurora?
❌ Avoid Aurora if:
- Simple single-AZ DB is enough
- You need super-custom DB internals
- You want total portability outside AWS


Auto storage increment in Aurora

- up start at 10GB storage and once those 10GB are filled, Aurora automatically adds new volumes with additional storage
- upto 128TB of automatic storage increment is available


Replication in aurora
- aurora supports upto 15 read replicas with a replication lag of sub 10ms
- replication process is faster than using standard MySQL RDS

Aurora High Availability & Read Scaling
how does aurora provide high availability


Aurora has the concept of writer and reader endpoints
both the writer and the reader have separate endpoints to connect to from the client application
the writer endpoint connects to a single writer instance or the primary DB instance
the reader endpoint connects to multiple reader instances and load balances between them
when a primary server fails then instead of changing the url where the client connects to, the writer endpoint will choose another aurora db as its primary server. This makes sure that a single and consistent endpoint will be used by the client application

read replica auto scaling
custom endpoints
aurora serverless
global aurora
babelfish for aurora postgresql

also both writer and all read replicas have the same shared volume or storage
such that when a new replica is promoted, it doesn't need to sync data with the master
