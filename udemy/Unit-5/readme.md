# Grouping and Aggregation 

## Grouping 
Reducing many rows down to fewer rows based on certain conditions that we place for it. For example, in the comments table which has a `user_id` for each comments, we can select all the unique `user_id` once and group them together temporarily. So let's take a table having `user_id` `1 3 3 4 1 5 2 2 1 3 4`. In the given collection of `user_id` we have numbers 1, 2, 3, 4, 5 (the repetition does not matter) grouped together with their own columns matching with the `user_id`. The numbers which comes first are placed first. For example, 1 is not followed by 2 but rather by 3 and 4 and 5 and at last with 2.
We use the `GROUP BY` statement to do so. 
`SELECT user_id FROM comments GROUP BY user_id` would do what we just mentioned above in the `user_id` example.
We get a group of records for the condition we specify. For each record we just get the value that we specified on the query for example in the above example, we grouped the records based on the different `user_id` so we can only get the results of the `user_id`. Other than the column `user_id`, we cannot get the value of other columns by grouping. To perform action on the groups that we created we can use aggregation to perform various operation on the records of the group. 

## Aggregation
The row that gets returned from grouping under certain condition can be used to aggregate a single result. The result will work for each group that gets returned. For example, from the above sql query we may get a result something like 1 then 3, 4, 2, 5. The aggregate function goes through all the rows with `user_id` 1 and then performs a particular action. Similar thing is done with rows having `user_id` 3 and so on.
There are various operation we can perform using aggregation which includes 
- COUNT() -> returns the total number of rows included in a particular group
- SUM()   -> returns the sum of all the values of the columns of each records of a particular group
- AVG()   -> returns the average value
- MAX()   -> returns the maximum value
- MIN()   -> returns the minimum value
When we are using `COUNT()` function for a column of a table neglects the row having a null value. For example, we have a photos table which has a url associated with a null value. When we say `SELECT COUNT(user_id) FROM photos;` we tell sql to return the total number of rows from the photos table having a `user_id` value. The above sql query counts all the rows except the row with the null value because that row is not associated with a `user_id`. To solve this problem we can use the * symbol inside the aggregate function to count all the rows of a table rather than all the rows having a `user_id`.

## Combining aggregates and grouping 
Let's take an example sql query
```sql
SELECT name, COUNT(*) FROM books JOIN authors ON authors.id = books.author_id GROUP BY authors.name;
```
Here we first the books and the authors table based on the condition `authors.id = books.author_id`. This creates a table with all the books having an author or all the authors having a book. Now we group a new record based on the author's name such that each group of author's name has the book corresponding to it.

## Using the group by and join statement together

## The order in which these keyword are placed on the sql query
- `FROM` -> when we read data from a table we have to use the `FROM` keyword to specify which table's column are we reading from. This is the first keyword that is used while reading data.
- `JOIN` -> when we want to join two or more tables together based on a certain condition then we use the `JOIN` keyword. This is placed after the `FROM` keyword is specified.
- `WHERE` -> when we want to filter out the table 
- `GROUP BY`
- `HAVING` -> used when we want to filter out a group

