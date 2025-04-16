in lamport clock each process in the system needs to have a local counter that follows specific rules:
1. the counter is initialized at 0
2. the process increments the counter by 1 before executing an operation
3. the process increments its counter by 1 after sending the mssage alongside the message
4. on the receiving side, the process merges the counter it received with its local counter by taking the maximum of the two and then increments the counter by 1 again
