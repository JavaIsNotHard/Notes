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

### Problem with data integration
what makes data integration hard?
the rise of trend of event data rather than state data. Most modern architecture deal with event driven architecture which means we are try to capture more event data (in a web application, it could be the amount of times the user clicked on something or when user logged in and how they logged in rather than the state information) than state data 
Event data are captured in a large volume that exceed state data which increases challenges during data integration. They are also unstructured in most cases since they are capturing raw facts from some point in time hence processing them can be hard

another challenge for data integration is the advancement of specialized data systems such as OLAP systems, search systems and more that require data to be of different types and formats depending on different types of data system used hence it greater complexity when dealing with data integration


### Log structured data flow

this flow is basically a publisher writing to its log and other subscribers read from this log and updating its own local log and advancing its position on the log

"the log concept gives a logical clock for each change against which all subscribers can be measured. This makes reasoning about the state of the different subscriber systems with respect to one another far simpler"

"A log concept gives a logical clock for each change"
what does this mean?
it means that a log has a sequence of events 
each event has a position in the log
the position acts as a logical clock so instead of relying on a timestamp, we rely on the position of the log to determine its progress

"against which all subscribers can be measured"
what does this mean?
this means that we can use the log to track how far they have progressed by noting the last log position they read 

"This makes reasoning about the state of the different subscriber systems with respect to one another far simpler"
what does this mean?
we can reason about the state of different subscriber i.e because of the log we know positions of subscriber in their log and can compare them with different subscribers to determine which log is in front or which is lagging and such 


