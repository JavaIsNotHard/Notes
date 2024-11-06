# Join Operation between tables and records 

## What does the join keyword do?
The join keyword basically merges the records or two or more than two tables and helps gather information from both of the table. The query we write to invoke or use the join keyword is:
```sql
SELECT * FROM table1 JOIN table2 ON table1.id = table2.id;
```

## When do you know when to use the join keyword? 
We use the join keyword between two or more than two tables or records inside the table when we want to show information of both the table simultaneously. 

## The order in which we write the names of the table between FROM and JOIN
The table which we write before the JOIN statement is the table whose each elements will be scanned by postgresql with reference to the second table that we pass after the JOIN statement. For example if we have a table called photos with the photo url and the user_id as a foreign key for a table called users then 
```sql
SELECT url, username FROM photos JOIN users ON photos.user_id = users.id;
```
Here, before then JOIN statement we wrote photos to loop through all the entries of the photos table and join users for each photos if the condition `photos.user_id = users.id` is true.

What happens now to the photos table when we add a photo url with a foreign key of NULL. When ran by postgresql, the photo with no association with the users table i.e photo url with foreign key NULL was not shown when we viewed all the photos of the table. Why is that? 
It is because there are no rows with id NULL inside them. So when there is a photo url with a foreign key of NULL, they are dropped from the overall result. Another thing to note is that the referenced table or `users` table in this case will never have a NULL primary key. 

## There are different kinds of joins in sql
### Inner join
Inner join is the typical join keyword that we use when we want to join two tables based on certain properties. The resulting table has only those properties of both the table which satisfies the condition that we initially gave which could be something like 
`ON photos.id = comments.photo_id`. 

### Left Outer Join
This returns all the rows of the left table and the matching rows of the right table based on the specific conditions. If there is no match between the left table and the right table then the value of the right table is discarded by the value of the left table that we couldn't find a match of will get a NULL value. For example, if we write a join statement for both photos and comments such that it returns all the photos associated with a comment but there are some photos which do not have a match on the right table. Then the left outer join will include the photos with no match along with all the photos will the match.

### Right Outer Join
Similar to the left join where all the records of the left table are returned. Here, all the records of the right table are returned which do not have a match with the left table. But it will not return the records of the left table with no matches. 

### Full Join
Here all the records of both table A and B are returned including those which do not have a match. Again the values of the records with no matches are kept as NULL for both the table.


## using WHERE inside of a join
This is particularly useful when we want to filter out the table that was produced as a output from merging two or more tables. For example,
```sql
SELECT url, contents FROM comments JOIN photos ON photos.id = comments.photo_id WHERE photos.user_id = comments.user_id;
```
The given query first merges two tables based on the ON statement which merges records of both photos and comments where each record of the photos has a comment associated with it. Then we have a second statement using the WHERE which then filters out the merged table such that only those records are shown whose user_id for both photos and comments are the same. 
This query essentially helps us to find those photos and the associated comments posted by the same user. The `photos.user_id = comments.user_id` WHERE clause helps us to do that. 

## joining more than two tables 
To join more than two tables we need to first merge the first two tables that are necessary and finally after the ON condition place another JOIN to join the third table along with the condition. 
