patterns when multiple consumer read from the same topic:

- [[load balancing by message broker]]
- [[fan out in message broker]]

- we can combine both the approaches into a single approach where we divide the consumers into groups i.e each group has multiple consumer node running
- each group are subscribed to the same topic such that all group receives all messages (fan out approach) and only one node inside a group receive the message (load balancing approach)


![[Screenshot 2025-05-09 at 1.33.43 PM.png]]

