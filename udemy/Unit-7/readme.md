# Sorting Records 

## Using the ORDER BY keyword
When we want to sort a record based on certain properties or conditions or particular column then we use the `ORDER BY` keyword. For example we have a table containing information about products that are sold in an e-commerce site, the table has a name column which includes the names of all the products that are being sold. We can use the `ORDER BY` keyword to sort the table based on the name of the product in an ascending or descending way. We can also use the product id to sort the record in ascending or descending way. 
```sql
SELECT * FROM products ORDER BY name; // name is a VARCHAR so the sorting would be done based on the alphabetical order
    
SELECT * FROM products ORDER BY id;   // id is a INT so sorting would be done based on numeric order
```

## Using the DESC and ASC keyword
Along with the `ORDER BY` keyword we can also use `DESC` and `ASC` keyword to make the sort descending or ascending respectively. If we were not to specify the order of the sorting then the default sorting is done as ascending. So we only need to add the `DESC` keyword when we have to sort the records in descending way. 

## Sorting using more than 1 properties
We talked about how we can sort using one property of a table but we can use multiple properties of the table to sort records in it. 
```sql
SELECT * FROM products ORDER BY price, weight;
```
The above query will first sort the table with respect to the price then it will resort the table based on the weight. We can use the `ASC` and `DESC` keyword in each of the properties individually such as 
```sql
SELECT * FROM products ORDER BY price ASC, weight DESC;
```
Here the price will be sorted in ascending order and the weight later will be sorted in descending order. 

## LIMIT and OFFSET keyword 
We use the `OFFSET` keyword when we can to skip some number of records in the table. We use the `LIMIT` keyword to only return records from the table based on the number given along with the LIMIT. For example, if we say `OFFSET 4` then this query would skip 4 records and then start with the fifth one. And if we say `LIMIT 2` then this query would only give results on the first 2 records. If the `LIMIT` that we give is more than the number of records we have in the table then all the records of the table are going to be printed.
We can mashup both the `LIMIT` and the `OFFSET` together to give our desired result. For example, in the products table we wanted to skip past 400 items and then print out the top 10 items afterwards then we would write a query something like this 
```sql
SELECT * FROM prducts ORDER BY price ASC OFFSET 400 LIMIT 10;
```
The query first sorts the table in ascending order then skips past the first 400 records and then gives the first 10 records from the table afterwards. We would use OFFSET and LIMIT to also show users the top 10 most viewed or top 10 most rated products in their site by using the following example query. 
```sql
SELECT * FROM products ORDER BY rating ASC LIMIT 10 OFFSET 0;

SELECT * FROM products ORDER BY views ASC LIMIT 10 OFFSET 0;
```
