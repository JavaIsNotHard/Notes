used in row oriented storage 

each operator has to implement an API that is provided from the system that is going to have 3 functions:
1. NEXT() -> give me the next tuple, parent operator calls its child operator for next tuple in the set, if the set has no more tuple to return then it returns a NULL marker or EOF marker
2. CLOSE()
3. OPEN()

allows for pipelined model where one operator passes data directly into another operator without storing intermediate result back to disk

in the pipelined model what happens is that for each tuple that it gets from calling the next() method, it processes it and immediately passes that to the parent operator in the query tree

in iterator model, the child only returns a single tuple to its parent operator which means that the parent has to call the child operator's next method until it sees eof marker

normally databases operate one pipeline at a time

pipeline breaker are operators in the query plan that waits for its child operators to return all required value before continuing its execution. one of the most common example of pipeline breaker is the join operator which waits for values from two relations to be filtered and everything before it can join based on some predicate.

in join operator when the child passes its tuple to its parent then it creates a hash table for the join algorithm if we are using hash algorithm for joining relations

