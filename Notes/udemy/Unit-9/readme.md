# sub query

## What are sub queries?
Queries that are written inside another query. 

## Understanding the result produced by various queries 
- Many row, many column
- One column and many row
- One row and one Column

## Rules of using subqueries 
- Any subquery that results in a single value can be used inside the select statement 
- Any subquery that results in a single value as well as subqueries that return one or multiple columns can be used inside the from statement and whose returned value will be used by the outer select statement. When we write a subquery for a from statement that returns a single value then the outer select statements or from statements should be compatible with each other. For example, 
`select max(price) from products;`
will return a single row and a single column so that means when we use the result of this sub query for the from statement, the outer select statement should also return a single value.
`select price from (select max(price) from products);`
In this case the price would return a single column but many rows which is not compatible with the result of the sub query so this produces an error. This is also true when we define the property `name` or `id` or anything that returns a single column but many rows. 
`select * from (select max(price) from products);`
In this case we want to return everything of that of the sub query. Since the sub query only produces a single result, this entire query would also produce a single result even though `*` normally returns the entire table.

Along with the `from` statement we can also use sub query that produces one or many columns with many rows. For example, 
`select name, price_to_weight_ration from (select name, price / weight as price_to_weight_ration from products);`
This query will return both the columns `name` and the column `price_to_weight_ration` since they are compatible with the outer select statement which also returns the `name` and the `price_to_weight_ration` column.

When using a sub query inside a `from` clause we need to add an alias to it (this is a rule) else we get an error.

When using a sub query inside the `JOIN` clause 
```sql
select first_name from users join (select user_id from orders where product_id = 3) as o on o.user_id = users.id;
```

When using sub query inside of an `WHERE` and `IN` clause. The structure of the data that must return from the subquery includes either a single column table or a single row single column value. The operators such as `< > != = <= >=` all use single row and single column value whereas operators such as `IN and NOT IN` uses single column table value.
```sql
select department from products where department not in (select department from phones where price < 100);
```
The above query has a sub query that returns the department column of the products table where the price is less than 100. Now we compare the original department column with the new department column with all the products where price is less than 100 and only select those departments which are not in the new department column. This way we are getting a result department that has all the departments that are not in the same department as products with price greater than 100.

There are other operators that we can use inside of sql to evaluate a value or a column returned by a sub query which includes `> ALL, < ALL, >= ALL, <= ALL, = ALL, <> ALL`. The `ALL` operator would check for all if all the values in the left matches the condition of all the values returned by the subquery `(left column value) > ALL (column returned by the sub query)`.
There is also the `SOME` operator which does something similar to that of the `ALL` operator but in the `SOME` operator there must be at least 1 value in the left column that matches the condition with the column returned by the sub query. `(left column value) > SOME (column returned by the sub query)`.

```sql
select name from phones where price > ALL (select price from phones where phones.manufacturer='SAMSUNG');
```

## Correlated sub query
This works like a nested for loop where for each row of one table we loop through all the column of another table.

```sql
select name, department, price from products as p1 where price = (select max(price) from products as p2 where p
 2.department = p1.department);
```
This above query is used to find the most expensive product of each department

```sql
select name, (select count(*) from orders as o1 where o1.product_id = p1.id ) from products as p1;
```
The above query is used to count the number of orders for the particular product

### NOTE: When doing division between a integer number and a temporary variable we do not get the decimal result. To get the result in decimal we need to cast the column of the table we want to divide to a decimal as `column::decimal / something`


```sql
select first_name, count(*), avg(price) from (select first_name, last_name, name, weight, price from orders join users_two on users_two.id = orders.user_id join products ON products.id = orders.product_id order by first_name) as p group by first_n
 ame;
```
