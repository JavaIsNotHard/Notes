
Deregistration Delay in ALB and NLB 

 basically allows target group instances to be removed from the target group by graceful shutdown, which means it allows the following:
- existing user request that are in flight or are being processed are completed first
- new connections are not allowed in this instance