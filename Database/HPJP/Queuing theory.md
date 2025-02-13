- response time -> time required to process a single request 
- throughput -> the no of time that. an be completed in a given time frame

- average time required for a request to be serviced 
	- depends on the long term request arrival rate 
	- average number of request in the system 
- let, 
	- W = average time a request spends in the system 
	- L = average number of request in the system (including both request that are being service and the ones being enqueue)
	- Then `L = arrival rate * W`

- suppose the txn response time is 100 ms or 0.1 s 
- suppose the arrival rate of the request is 50 request per second 
- then the average no of request in the system in a time is L = 0.1 * 50 = 5 connection
- this means that if the pool size is 5 then 5 connection can be acquired without having to enqueue any request
- but if the pool size is 3 then if 5 connection request were to be received then 3 can acquire the connection and 2 has to be enqueued 

