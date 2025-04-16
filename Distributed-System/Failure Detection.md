in a networked system there are many things that can go wrong, one of them being hard to detect failure 

failure detection is hard because the client has to know whether the lack of response from the server is due to a failed server or due to network latency

in the worst case, the client will wait for the server
at the best case, the client will make an educated guess about the time it needs to wait 

another problem is that making the educated guess is also hard in our system because
1. making the guess too short, the client might wrongly assume the server is unavailable 
2. making the guess too long, the client will wait for response that will never arrive

another method is to make a list of available server using pings or heartbeats instead of waiting for the server
ping -> periodic request that a process sends to another to check whether it's still available. the sending process expects a response to the ping within a specific time frame and if not response is received, time out is triggered and destination is marked unreachable. the ping message is send regardless to check if the server has come back online
heartbeats -> message that is periodically sent to another processes, all the servers in the system will send periodic heartbeats to one another, if the destination doesn't receive a heartbeat within a specific time frame it then triggers a timeout and considers the other process unavailable

