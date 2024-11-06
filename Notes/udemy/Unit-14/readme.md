# Database-side Validation and Constraints 

## Row level validation 
This includes :
- if the given value is defined or not 
- if the value is unique in its column or not
- if the value is >, <, and other relation with some other values in the column 

NOTE: When working with one database we cannot connect to another database using SQL even if they are running in the same server.

## Using the `ALTER` and `NOT NULL` keyword if the value is not defined in the insert statement
`ALTER TABLE products ALTER COLUMN price SET NOT NULL`

## Using the `DEFAULT` keyword if we do not know the value we want to insert 
`ALTER TABLE products ALTER COLUMN price SET DEFAULT 999`

## Checking if the given value is unique or not
`ALTER TABLE products ADD UNIQUE(name of column)`

## Using the `CHECK` constraint for logical comparison

## Constraints 
- DEFAULT
- NOT NULL
- PRIMARY KEY
- UNIQUE
- FOREIGN KEY
- CHECK


## Removing a constraint from a column
`ALTER TABLE products DROP CONSTRAINTS products_name_key`
`ALTER TABLE products DROP CONSTRAINTS products_name_department_key`

`ALTER TABLE products ALTER COLUMN user_id DROP NOT NULL`

`ALTER TABLE products ADD COLUMN <name of the column> <data type> <constraints>`

`ALTER TABLE products DROP COLUMN <name of the column>`


NOTE: When we are applying a constraint after we create a table we need to keep in mind that there should not be a row that does not satisfy the condition beforehand
For example, we do something like `ALTER TABLE products ADD UNIQUE(name)` to only allow unique names in the table. Now if one of the record in the table already has a value that are not unique i.e there are two or more records having the same name then we cannot apply the constraint. We first have to remove those rows or update the values of those rows and then apply the constraint.
