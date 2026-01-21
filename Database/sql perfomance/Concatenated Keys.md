a primary key composed of more than one primary key

```
CREATE UNIQUE INDEX employees_pk
    ON employees (employee_id, subsidiary_id)
```

this creates a composite index made up of employee_id and subsidiary_id

```
SELECT first_name, last_name
  FROM employees
 WHERE employee_id   = 123
   AND subsidiary_id = 30
```

because we have created index on both employee_id and subsidiary_id, this uses the index to perform INDEX UNIQUE SCAN

but if we search using a single column from the composite key as such 
```
SELECT first_name, last_name
  FROM employees
 WHERE subsidiary_id = 20
```

then this peform a TABLE ACCESS FULL scan

the order in which we create a composite index also creates the sorting order of the data in the index
for example if we created an index on firstname and lastname and the values are as follows: ("Ab", "XYZ"), ("Aa", "XYZ")
notice how the values of the second column on both the rows are the same "XYZ" but the sort order is deteremined first by the firstname so "Aa" will before "Ab"



we can search based on the first element of the index only but we cannot search based on the second element only



[[bitmap index scan]]



two-index or more index delivers very good select performance
but the single index solution is preferable. it saves storage space but also maintenance overhead of the second index. 
the fewer indexes a table has, the better the insert, delete and update performance

finding the optimal concatenated index is hard because knowing the data access path is hard

creating index based on performance of a single query can affect the performance of other queries which depended on the previous query or better yet if one knew the access path of all the queires then it would be the best on creating an index
