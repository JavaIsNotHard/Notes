- database persist data either until the user explicitly deletes the data item or there is some hardware failure whereas message brokers delete the message when it is consumed by the [[consumer]]
- database supports primary and secondary indexes to search for data item stored inside it whereas message broker provides a way of subscribing to a subset of topics matching some pattern. both approaches selects data that it wants to know about 
- queries can be performed in database based on snapshot of the database when the query was processed whereas message broker do not support queries but do notify the clients when data are changed 

