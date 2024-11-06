# Basic query tuning

## What are the steps involved when executing a sql query
Parser -> Rewriter -> Planner -> Execution

1. First the query is sent to a parser to make the query more sensible to postgres, it dissects the query into various step also known as a query tree or parse tree, which represents the structure of the instruction. This contains information about all the conditions, the table to read from and many more.
2. Then the query is fed to the rewriter (not explained in much detail in this section so will leave for later references). The parse tree is then analyzed to rewrite the query to make sure that the query complies with the rules of sql.
3. The query is then passed into the planner which makes plans on how to execute the query, either to use index or just manually select all the rows of the table into the memory and so on. 
4. The execution is the last step which displays out required output

## How to use Explain Analyze keyword to inspect our query further
The explain analyze keyword produces a query plan for our query. The query plan contains information about how the query is to be executed and how long it would take for the postgres to do so.
There are some statements or rows with "=>" symbols from the output produces by the `EXPLAIN ANALYZE` which represents `query node`. These are steps which are trying to access some data from the database or tying to perform some operation on the data from the database. Each node passes values from one node to another node.

Each node contains information about the cost of operation, the number of rows and the size of the data present in each rows. NOTE that these values are approximate values and may not be accurate enough. When we just use the `EXPLAIN` keyword in front of the query, we get a planner tree as a result without executing the sql itself, it will also have all the values such as cost, width and length while excluding the actual time of operation took by the query.
![[Sat Jun 24 12:47:32 PM +0545 2023.png]]
(the blocks in the right side is the query planner and the left side is how the operation is going to be performed. For example, in the left side we see that the result produced by the index scan block is sent to the hash block, the result from the seq scan block along with the result of the hash block is then fed into the hash join block to finally get the desired output)

Now, when we just use the `EXPLAIN` keyword how can postgres estimate the values of cost, width and length without the query getting executed? The answer lies in the table that postgres uses to keep detailed statistics about what is going on inside each of the table. For this we use the query 
`SELECT * FROM pg_stats WHERE tablename='name of table';`


