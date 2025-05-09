- joins two sorted list like a zipper 
- both sides of the join must be sorted by the join predicate i.e JOIN ON attribute 

- for the user activity event and the user information database example, the user activity event file can be an input for one mapper and the user database be input for the next mapper 
- here User ID is the join predicate and sort key for both the tables 
![[Screenshot 2024-12-12 at 2.05.28 PM.png]]
- we can also impose an secondary sort order for the values of the input for the reducer
- the user id from both the activity event and the user database are going to be same such that we can merge those results into a single unique record 
- this merged record will contain the user_id, YOB, urls associated with the user_id 
- then the reducer can use this input to produce a URL to DOB mapping and can be used as input to a second MapReduce job 


the mapreduce framework sorts the record by key before they reach the reducer. but for the key itself, the value is not sorted. the order in which the value arrives in the reducer differs between different map reduce job because they come from different map jobs which may finish at different time
this is why secondary sort is required, the secondary sort makes sure that the values in the reducer are sorted by some combination of composite key


## Bringing related data together in the same place 
- since the reducers are partitioned based on the hash of the key, the key acts as the location of the value for the reducer
- for each key-value pair that the mapper produces, its key will guide the path towards the particular reducer job 
- map reduce also separates the concert of network communication with application code by performing the network communication on behalf of the application code such that the user can only focus on writing the application code 
- in case of failure during network communication, MapReduce transparently retires failed task without affecting the application logic


## GROUP BY 
- another usage of bringing related data to the same place is grouping records by key 
- the mapper sorts all the key-value pair based on key which produces a group based on the key
- this group of key-value pairs' value can be used to perform various GROUP BY operations such as filtering, aggregating, counting and more 
- to perform the operations, the mapper needs to bring all the items that forms a group into a single reducer 

## SKEWS 
skewed joins method in Pig first runs a sampling job to determine which keys are hot
when we perform the actual join, the mappers send any records relating to a hot key to one of several reducers, chosen at random 