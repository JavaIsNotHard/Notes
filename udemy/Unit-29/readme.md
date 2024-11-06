# Optimizing queries with materialized views 

## # Write a query to show the number of likes and comments received in each week.

## TODO:
- based on the created date we group by the record based on weeks, so we divide the table in intervals of 1 week 
- within that 1 week we will specify the post_id related to the created at 
- within that 1 week we will also specify the id from comments table related to the created_at value
- then we will count the number of post and number of columns separately based on that 1 week interval 

## How to approach the query: 
- The likes table in our instagram database has both the post_id and a comment_id to specify that a unique like is for either a comment of a post. Now we can take advantage of this clever schema design by joining the tables likes with both posts and comments table. 
- We want to left join the tables rather than inner join because each like has either the post_id or a comment_id. If it has a post_id then the comment_id is set to NULL and vice versa. 
- When we join the likes table and posts tables like `SELECT * FROM likes LEFT JOIN posts ON posts.id = likes.post_id`, if the value of likes is NULL then the entire column of the likes table is set to NULL, similarly if we join the likes table and comments table like `SELECT * FROM likes LEFT JOIN comments ON comments.id = likes.comment_id`, if the value of the comment_id in the comment table is NULL then the entire column of the comment table is set to NULL. 
- Now we have to join all the tables like this 
```sql 
SELECT *
FROM likes 
LEFT JOIN posts ON posts.id = likes.post_id
LEFT JOIN comments ON comments.id = likes.comment_id;
```

The first step to the query is solved where we have to join both the posts and comments table with the respective likes table. 
Now to group by each week we can use the `date_trunc` function. NOTE that the `date_trunc` function starts the week from MONDAY not SUNDAY. This function rounds down the current date to the nearest MONDAY
so if 2023-06-23 was FRIDAY then the `date_trunc` function would round down the date to 2023-06-19 which is a MONDAY.
```sql 
SELECT 
	date_trunc('week', COALESCE(posts.created_at, comments.created_at))
FROM likes 
LEFT JOIN posts ON posts.id = likes.post_id
LEFT JOIN comments ON comments.id = likes.comment_id;
```

This returns all the created_at date to the nearest MONDAY date. Now for each week in descending order we could group by the created_at column and count the values in the column 
1. First sort by descending order created_at
```sql 
SELECT 
	date_trunc('week', COALESCE(posts.created_at, comments.created_at)) AS week
FROM likes 
LEFT JOIN posts ON posts.id = likes.post_id
LEFT JOIN comments ON comments.id = likes.comment_id;
ORDER BY week DESC;
```
2. Group by the created_at column 
```sql 
SELECT 
	date_trunc('week', COALESCE(posts.created_at, comments.created_at)) AS week
FROM likes 
LEFT JOIN posts ON posts.id = likes.post_id
LEFT JOIN comments ON comments.id = likes.comment_id;
GROUP BY week 
ORDER BY week DESC;
```
3. Finally we would add the count of likes for each week 
```sql 
SELECT 
	date_trunc('week', COALESCE(posts.created_at, comments.created_at)) AS week,
	COUNT(posts.id) AS num_likes_for_post,
	COUNT(comments.id) AS num_likes_for_comment
FROM likes 
LEFT JOIN posts ON posts.id = likes.post_id
LEFT JOIN comments ON comments.id = likes.comment_id;
GROUP BY week 
ORDER BY week DESC;
```
Since the id column of some of the records of both posts and comments are NULL the `COUNT` function would ignore those and only count those values which are not NULL. 

# Using materialized views
Materialized views are views that are ran on a certain time interval be that a day, a week or a month. We make materialized views of those queries that takes a lot of time to return a result. The result of the materialized view is stored internally inside postgres once such that the next time we have to access that result we would do so is lesser time or in a split second. We create a materialized view using the syntax 
```sql 
CREATE MATERIALIZED VIEW weekly_likes AS (
	<statements> 
);
```

We run the materialized view once and then it stores the result internally inside postgres. We access the result of the materialized view using 
```sql 
SELECT * FROM weekly_likes;
```

Since the query that we create in the previous section took a longer time to execute than normal we could make a materialized view out of it like 
```sql 
CREATE MATERIALIZED VIEW weekly_likes AS (
	SELECT 
		date_trunc('week', COALESCE(posts.created_at, comments.created_at)) AS week,
		COUNT(posts.id) AS num_likes_for_post,
		COUNT(comments.id) AS num_likes_for_comment
	FROM likes 
	LEFT JOIN posts ON posts.id = likes.post_id
	LEFT JOIN comments ON comments.id = likes.comment_id;
	GROUP BY week 
	ORDER BY week DESC
);
```

## Problems with materialized views: 
- When we make changes in the values that are associated with the views that we create for example if we change the value of the posts table then it does not affect the result produced by materialized views since it has already stored the result of the last query somewhere. 
	- To solve this we have to `REFERESH` the materialized view each time the value inside the tables associates with the views changes like 
```sql 
REFERESH MATERIALIZED VIEW weekly_likes;
```
Each time there is a change in the table that are associated. 


## Differences between normal views and materialized views
Normal views are just fake tables but materialized views store the result of the values rather than creating a fake table for other use. 
