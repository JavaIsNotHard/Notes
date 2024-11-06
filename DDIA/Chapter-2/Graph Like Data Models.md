There are different ways of structuring and querying data in graphs. The **property graph model**  and **triple-store model** are two types of graph model. 

![[Screenshot 2024-10-18 at 07.55.36.png]]

## Property Graph 
In this model, the vertices of the graph must contain the following: 
1. A unique identifier 
2. A set of outgoing edges 
3. A set of incoming edges
4. A collection of properties (key-value pairs)

The edges of the graph must contain the following: 
1. A unique ID
2. The vertex at which the edge starts 
3. The vertex at which the edge ends 
4. A label to describe the relationship between the two vertices 
5. A collection of properties (key-value pairs)

## The Cypher Query language 
A declarative query language for property graphs for Neo4j database. 

![[Screenshot 2024-10-18 at 07.50.50.png]]

Fig: A subset of data in Figure 2-5, represented as Cypher Query

When all the vertex and edges of the graph are created using the Cypher query language we can start asking questions to the database such as find all the people who emigrated from US to Europe.
Find vertices that has a BORN_IN edge to a location within the US and also a LIVING_IN edge to a location in EUROPE

![[Screenshot 2024-10-18 at 10.55.17.png]]

## Graph Queries in SQL 

