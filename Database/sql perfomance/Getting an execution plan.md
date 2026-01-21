execution plan is fetching by putting the `explain` command in front of an SQL statement, SQL statement with bind parameters cannot be explained this way, they need to bee prepared first 

Anatomy of an execution plan

EXPLAIN: the base command. it estimates the plan using table statistics (collected by autovacuum daemon). it does not execute the query

ANALZYE: executes the query. it discards the result set but captures the actual run times and row counts._Warning:_ Do not use this on `INSERT`/`UPDATE`/`DELETE` unless you wrap it in a `BEGIN; ... ROLLBACK;` block, or you will modify your data!

BUFFERS: it tracks buffer cache usage, it tell you how many pages or blocks were read from memory vs disk, it can only be used with ANALYZE because it needs to run the query to count

