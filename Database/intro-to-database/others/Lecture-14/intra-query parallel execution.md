parallel execution of a single query by splitting the query into multiple tasks then each task is ran in parallel to one other 

this execution has an [[exchange operator]]

```
SELECT A.id, B.value 
FROM A JOIN B
ON A.id = B.id 
WHERE A.value < 99
AND B.value > 100
```

This produces a query plan such as 

```
projection
	|
	|
   Join

Filter  Filter

A         B
```

