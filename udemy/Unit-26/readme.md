# Common Table Expression (CTE)

This is a method to simply the sql query that we write into something readable and clean. We create a common table expression using the `WITH` keyword. We usually use common table expression when we want to join two tables but the second table is the result of an operation rather than an existing table. This is used in place of a subquery returning a table rather than a single value. 
For example, 
`SELECT user_id, created_at FROM photo_tags UNION ALL SELECT user_id, created_at FROM caption_tags`
This query would return a table with user_id and created_at columns. We can then create a common table expression of this query using the `WITH` keyword 
```sql
WITH tags AS (
	SELECT user_id, created_at FROM photo_tags 
	UNION ALL 
	SELECT user_id, created_at FROM caption_tags
)
```
Now we can refer to the return returned by the query inside the () as tags.