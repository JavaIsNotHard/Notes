# The GREATEST keyword

We can use the `GREATEST` keyword to find the greatest value in a given list of values. For example, if we wanted to select the number 30 if the product of the `price` * 2 is > 30 then we could use the query 
```sql
select name, weight, GREATEST(30, price * 2) from products;
```
The above query would either return 30 or price * 2 if price * 2 is greater than 30. This would repeat for each row of the product table.


# The LEAST keyword 

Similar to the `GREATEST` keyword we can also use the `LEAST` keyword to get the least value from a given set of values. This can be helpful when we wanted to place all the products for sale. If price * 0.5 is less than 400 than select that price else we will keep the value of the product as 400. 
```sql
select name, weight LEAST (price * 0.5, 400) from products;
```
If price * 0.5 is less than 400 then select that price else select 400 as a value for that product.


# The CAST keyword

This is very similar to the switch cast statement in a programming language in which for each value we have a unique operation to perform. We begin the case by using the `CASE` keyword and end the cast using the `END` keyword we also use the `WHEN` keyword to specify which operation to perform for a given case. 
```sql
select name, price,
    case
        when price > 600 then 'HIGH'
        when price > 300 then 'MEDIUM'
        else 'LOW'
    end
from products;
```
