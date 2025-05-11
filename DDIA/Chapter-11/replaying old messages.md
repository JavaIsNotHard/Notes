- JMS/AMQP style message brokers are destructive standards since they delete the message when consumed and when ack is received
- on the other hand log based are stored on disk and persist until it exceeds its threshold

- the consumer's offset is controlled by the consumer and it can easily manipulate the offset value
- this makes it possible to set the consumer offset to point to where it pointed in the past such that the consumer can start reprocessing the messages and hence replaying old messages which makes this very similar to batch processing system

