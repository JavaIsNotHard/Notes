by separating mutable state from the immutable event log, you can derive several different read oriented representation from the same log of events, we could have a database derived from the log of events, we could have a search engine derived from the log of events and much more 

there are existing system that utilize this functionality such as the analytic database druid which ingests directly from kafka, kafka connect sinks can export data from kafka to different databases and indexes 

we can also have different schemas database as different consumer of the event log, if we want to introduce a new feature that uses your existing data in some new way, you can use the event log to build a new read-optimized view for the new feature. this reduces work that was done through migration files in the same database 

storing data in a data store is simple  if you don't worry about how it is going to be queried or accessed 