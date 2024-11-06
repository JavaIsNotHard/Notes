# 1.1 Database design process 
- What kind of things are we storing
- What properties does this thing has
- What type of data each properties contains 

For example if we were trying to design a database about all the large cities in the world which also contains information such as the name of the city, the country the city belongs to, the population of the city and finally the area of the city. 
Now we can use the above mentioned list of processes involved to create a high-level overview such as:
- We are storing the list of the cities 
- Each list contains the name, the country, the population and the area
- name -> string, country -> string, population -> integer, area -> integer 

## 1.1.1 Database Terminologies
- **Tables**: They are the most crucial component of the database since we store all information inside a table. 
- **Columns**: Each table has their own separate columns which are typically used to represent the attributes or properties of the data that we are trying to store. For example the name column would include the name of the cities, population column would include the population of the cities.
- **Rows**: Each table has a collection of rows and each row represents a single data that is being stored. For example the first row has the city name 'Tokyo' which are defined or identified using the corresponding column elements such as country name, population and area. 

## 1.1.2 SQL
SQL stands for structured query language which is a standardized programming language which is used to make relational database such as mysql, postgresql, sqlite and many more. It also sets up a standard that all other new database models need to comply on. 

## 1.1.3 Using a database
To properly set up the database according to our design that we have created above, we first have to create a **table**. To create a table in SQL we use the command `CREATE TABLE <table-name>`. To create the properties inside the table we list out the names of the properties that we want to create and its type. For example since the cities are string, we use the keyword `VARCHAR` to tell SQL that we are creating a property called cities and its data type is a `STRING`.

## 1.1.4 Understanding the SQL commands
There are keywords and identifier inside SQL just like any other programming language. Keywords are predefined by the SQL programming language whereas identifiers are special names that we programmers give to a particular object. Keywords in SQL are also written in capital letters whereas identifiers are usually written in lower-case. We can insert into the table using the `INSERT INTO <name of table>` command followed by the parameters or the rows that the schema or the table has inside a square bracket like the following 
```sql
CREATE TABLE cities (
    name VARCHAR(50),
    area INT
);

INSERT INTO cities(name, age) VALUES ('Kathmandu', '141360');
```
Till now we have been able to create and insert into a table or a database schema but we still need to be able to update, delete and view the schema. To view the schema or the table we created, we use the `SELECT * FROM <name of table>` command. To further expand the example we will take the cities table from the above snippet.
```sql
SELECT * FROM cities;

SELECT name FROM cities;

SELECT area FROM cities;
```
The `*` is used to indicate that we are trying to select all the rows that are present in the schema and view it. We can also view individual columns using the name of the column or the table property.

## 1.1.5 Math operators 
There are various operators that we can use among various columns or properties in SQL like `+ - * / ^ |/ @ %` where `^ |/ @ %` are exponent, square root , absolute value and remainder respectively.

## 1.1.6 String operators
Like manipulating the INT properties of the table, we can also manipulate the strings present in the table using the following operators `||` for joining two strings, `CONCAT()` to concat multiple strings together, `LENGTH()` to get the length of the string, `LOWER() UPPER()` for getting the lower and upper representation of the property.


