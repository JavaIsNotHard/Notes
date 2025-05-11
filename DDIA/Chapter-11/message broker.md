- a type of database that is optimized for handling stream events 
- the broker runs as a server which both the producer and the consumer connect as a client
- producers send new events to the broker whereas consumers receive the event by reading from the broker 

- the broker lies central for both the producer and consumer hence many capabilities such as durability can be placed on the broker itself rather than the producer or consumer
- the broker stores most messages on its local in memory buffer and can also write them to disk for durability
- they allow unbounded queuing of messages
- as a consequence of queueing, this makes the producer act asynchronously i.e it does not wait for the consumer to finish processing the message before moving on and only waits for the acknowledge from the broker on whether it received the message or not
- message brokers allows for unbounded queueing as opposed to dropping messages and backpressure

[[message broker compared to database]]

- message brokers have standards such as JMS and AMQP and are implemented by software such as RabbitMQ, ActiveMQ and so on 

[[multiple consumers]]

[[acknowledgements and redelivery]]

[[log based message broker]]
