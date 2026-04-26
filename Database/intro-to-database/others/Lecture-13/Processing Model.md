Defines how the system executes a query plan and moves data from one operator to the next 

processing model is comprised of two types of execution paths:
1. control flow : Deals with how DBMS invokes an operator
2. data flow : How operator sends its result to the next operator and so on


processing model approaches:
1. [[Iterator Model]] -> most common
2. [[Materialization Model]]
3. [[Vectorized Model]] -> used in OLAP systems