# Union and Intersection With Sets

## Handling Sets with Union
When we have two different query that gives us an identical result then we can use the `UNION` or `UNION ALL` keyword to join the two queries as one and give the resulting table as the joined result of both the first and the second query. The `UNION` keyword will filter out any common records that we might get when we get the result from both the query where as the `UNION ALL` keyword would not filter out the common record and would include the common record in the result as well.  
Again one thing to note is that we cannot `UNION` two different queries that give out different results from one another. For example, one query would give all the name of the products in the table and the second query would give all the price of the products in the table, in this case the type of the result that is being returned is not the same (because name is a VARCHAR and price in an INT). But we could `UNION` out two query such as 
```sql
SELECT * FROM products WHERE price > 1000 UNION SELECT * FROM products WHERE price < 1000;
```
Here the first query would return the entire table as does the second query so we can indeed union both the query.

## Commonalities with Intersect 

## Except 

