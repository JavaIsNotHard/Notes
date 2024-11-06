# PostgresSQL Complex Datatypes


## What are different data types available in postgresql
The most commonly used data types in postgresql include : data type working with numbers, data type working with date and time , data type working with characters and strings and data type working with boolean values such as true and false.

Data type working with numbers include :
- `Numeric` and `Decimal` data type to represent accurate decimal numbers and decimal arithmetic
- `Float`, `Double Precision` and `Real` data type of represent floating point numbers but are slight inaccurate than `numeric` and `decimal` data type.
- `smallint`, `int` and `bigint` data type to represent integer numbers that are not decimal.
- `smallserial`, `serial` and `bigserial` data type to represent serial integer numbers that auto increment.

Data type working with characters include: 
- `CHAR(size of character)` data type to insert characters of length that is equal or less than the size of the character specified
. If the character stored is less the size of the character specified then postgres adds padding to fill the size of character with empty spaces.
- `VARCHAR(size of character)` data type similar to the `CHAR` data type but padding is not done in this data type. 

So when to use `CHAR` and when to use `VARCHAR`? 
If we want a column where the size of character of all the entries are to be of the exact type then you can use the `CHAR(size of character)` data type but still using `VARCHAR` is preferred more. 

- `TEXT` data type is similar to the `Varying character` in a sense that it is not of fixed size. 

Data type working with boolean type include:
- `TRUE`
- `FALSE`
- `NULL`


