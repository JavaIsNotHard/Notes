- computation unit in stream processing
- self contained, immutable object that contains some information about the events that happened and also a timestamp to indicate when it happened. 
- example of events include, activity that user performs in your website or a sensor that measures temperate every few seconds 
- it can be encoded in plain text string, JSON, or in some binary formats such as protobuf or avro
- encoding the events allows you to store the event in file, or in database or can also be used to transmit over the network 

- related events are grouped together into a [[topic]] or stream

- an event is generated by a [[producer]] and the processed by multiple [[consumer]]
- a database is enough for a [[producer]] to produce and for the consumer to continuously poll the database for any new data and consume the data. this is how batch processing system operates

- for building a system with low latency, polling is not a good option instead there needs to be a mechanism for the producer to notify the consumer about new events that appear
- this new approach is known as [[messaging system]]