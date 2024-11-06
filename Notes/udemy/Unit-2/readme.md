# 2.1 Filtering Records 

## 2.1.1 Comparison Operators 
SQL being a programming language also has support for comparison operator like a normal programming language. The comparison operator includes `= != > < <= >= <> BETWEEN IN NOT IN`. But before the comparison we need to use the `WHERE` keyword.

## 2.1.2 Update records
We use update to a particular value of a particular row or record. Update is not equivalent to using the `ALTER` keyword, update is just used to update a value not the composition of a row.
`UPDATE <name of table> SET <column> WHERE <condition>`

Let's take a example sql query
`UPDATE products SET price 500 WHERE id=100`
This query updates the price to 500 of the row whose id=100


## 2.1.3 Delete records
`DELETE FROM <name of table> WHERE <condition>`

To delete a row that has a value of NULL we use the query

`DELETE FROM products WHERE price IS NOT NULL;`
