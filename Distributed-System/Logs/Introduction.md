why logs?

1. ordering changes 
2. distributing data 
3. agreeing upon a change 


## the state machine replication principle 

if two identical, deterministic process begin in the same process and get the same input in the same order, then they will end up with the same output and end in the same state


deterministic process -> process that is not timing dependent and doesn't let an out of band input influence the result

a function that calls the time of day method inside it is a non-deterministic or a function that calls the random method is also non-deterministic because calling those function would result in two different values between two different machines 

the state of the machine is whatever data remains on the machine either in memory or in disk at the end of processing

## What a log is good for?

1. data integration -> making organizational data easily available to all its services and system 
2. real-time data processing 
3. distributed system design


### Data integration

means, making data that an organization has available in all its services
ETL also falls into data integration which basically populates a relational data ware house
Data integration is also responsible for combining data from multiple sources into a unified system 
data integration can be batch processing that loads data into a data warehouse but it can also deal with real time data 
before you can do anything useful with data (like analyze it, visualize it, or build ML models), you first need to **gather it from all its different sources, clean it, and make it available in one place where people or systems can actually use it.**
only then the data is available for further processing like MapReduce, Hadoop and more 
since data integration is so important how to build a reliable data flow throughout all the data systems in the organization?

