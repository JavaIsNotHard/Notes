A star schema contains a central table called the fact table 
the fact table is surrounded by multiple dimensions table
each item in the fact table represents an event that occurred at a particular time 
a row in a fact table for a e-commerce site could contain a customer's purchase of a product
if we were analyzing website traffic rather than retail sales then each row might represent a page view or a click by a user

some of the columns of the fact table are attributes such as price, quantity and stuff of the product while other are foreign key references to other table called dimension table 

another variant of the snow schema is called the snowflakes schema which further breaks down the dimension table into sub dimension table 

in production grade schema, the fact table are wide containing about 100 columns or even more 

![[Screenshot 2025-05-06 at 3.04.00 PM.png]]

