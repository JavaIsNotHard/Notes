# Simplifying queries with views 

In our Instagram database, we have used many queries which has made us merge both the caption_tags and photo_tags table multiple times. So the question is whether making the caption_tag and photo_tag table different a bad choice or a bad schema design? 

Since we have to union both the table multiple times and there are no visible performance benefits that we get out of separating both of these table we might just have a bad schema design. 

Now, what are the remedies that we can apply to solve this problem?
1. We can merge both the tables into a single table where it contains all the information necessary for both the table, insert the values into the new table (we can use the query `INSERT INTO <name of table>(values) SELECT <needed values> FROM <other table>`. This query selects the needed column or records from the old table and inserts into the new table) and delete the old table. 
	- Now what are the disadvantages of using this method?
		- we can't copy over the id's of the records of both the caption_tags and the photo_tags since they are unique (for example, if we have a record of id 10 at table photo_tag but we also have another record of id 10 at table caption_tag then the record with id 10 from either of the table would remain the same i.e 10 when they are inserted into the new table). This would also mean that any foreign key referencing to the id 10 of the photo_tag would not be valid since there are two records with id 10. 
		- The other problem is that if there are queries that depends on either caption_tag and the photo_tag then now it would not work any more.
2. The other solution is using "views".

## What are views? 
Views are fake table that has rows from other tables. They exist as part of all the other tables but are not considered as tables since running `\dt` doesn't show the name of the view that we created. 
Views do not create a new table or move data around. We can create views using the `CREATE VIEW <name of the view> AS ();` syntax similar to that of creating a common expression table. 
### Using views practically:
Views are similar to CTE's but views persist in the harddisk after its creation like tables. So the use case of views are also very similar to the use case of CTEs. 
For example, if we had to work with the 10 most recent post in our Instagram database and use various queries within the 10 most recent post then instead of creating a subquery to recent the 10 most recent post in every single query that we write, we could instead create a view something like this:
```sql
CREATE VIEW recent_post AS (
	SELECT * FROM posts ORDER BY created_at DESC LIMIT 10
);
```

Now we can use this view to run other queries like returning the username of those most recent 10 posts something like this:
```sql
SELECT username FROM users join recent_post ON users.id = recent_post.user_id;
```

### Altering and dropping view
We can also alter and drop views that we create. We alter a created view using the keyword `CREATE OR REPLACE VIEW <name of view> AS ();`
So, using our previous `recent_post` view that we created
```sql 
CREATE OR REPLACE VIEW recent_post AS (
	SELECT *
	FROM posts
	ORDER BY created_at DESC
	LIMIT 15
);
```

We can also drop the view that we have created using the `DROP` keyword. 
```sql
DROP VIEW recent_post;
```

