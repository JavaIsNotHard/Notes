what system model is?
- expectations about the behavior of processes, communication links and timing 
- so basically it is assumptions that we make of the system by ignoring the complexity of the underlying implementation details
examples about communication links assumptions
1. fair-loss link model -> assumes that the messages in this model may be lost or duplicated but if the sender keeps retransmitting the data then it will eventually be delivered to the destination
2. reliable link model -> messages in this model is delivered exactly once without loss or duplication

examples of process assumptions:
1. arbitrary-fault model -> assumes that a process can deviate from its algorithm in arbitrary ways leading to crashes and unexpected results 
2. crash-recovery model -> assumes that a process doesn't deviate from its original algorithm but can crash and restart at any time
3. crash-stop model -> assumes that a process doesn't deviate from its original algorithm but also doesn't come back online after crash

examples of timing assumptions
1. synchronous 
2. asynchronous 
3. partial-synchronous
