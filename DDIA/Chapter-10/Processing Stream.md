we know where streams comes from  (user activity events, sensors, writes to database)
we also know how streams are transported (through direct messaging, message broker, event log)

what can we do with stream once we have it?
You can process one or more input streams to produce on or more output stream 
streams may go through a pipeline consisting of several processing stages before eventually reaches to its final output

the pipeline consists of several processing jobs or stages which can perform various tasks such as filtering, aggregating, joining, transforming and more

one crucial difference between stream jobs and batch jobs is that stream never ends 
so sorting cannot be done to an unbounded dataset and hence merge sort joins cannot be performed as a join operation 
also fault-tolerance mechanism also changes between them, a batch job can be restarted in a different node when a processing node dies whereas restarting a stream job that was running for several years from the start doesn't make sense 

one of the major use of stream processing is for monitoring purpose
other applications of stream processing includes:
1. complex event processing: used to analyze the stream of events that passed through the system and look for complex conditions, not just individual events but combination of groups of events that have special meaning. like how regular expression allows you to search for complex character pattern in a string, CEP allows you to specify rules to search for certain patterns of events in a stream. 
       CEP uses high-level declarative query language like SQL to describe the event pattern that we are trying to capture. the queries are submitted to the processing engine which also consumes the input stream. the events are ran through the queries and when a match is found then then engine emits an complex event 
       the relationship between the query and the database is reversed in CEP. in traditional database, query is performed after data is persistent in the database whereas in CEP events from the inputs stream continuously flow past the engine which matches the incoming events against the stored pattern in real-time 
2. stream analytics: the boundary between CEP and stream analysis is blurry meaning that they are very similar in nature. analytic tends to be less interested in finding specific event sequence and is more oriented towards aggregation and statistical metrics over large number of events. Instead of using exact statistical algorithms, stream analytic prefer probabilistic algorithms such as bloom filter for set membership and hyperloglog for cardinality estimation. this is because of the low memory consumption that probabilistic algorithm has over traditional statistical algorithms that use a lot of memory when the dataset is large 
3. maintaining materialized view: we can also use stream changes to create a materialized view based on the current state of the database i.e now the derived system is the materialized view which can be constructed is ways that is required by the business logic which is different from the main database 