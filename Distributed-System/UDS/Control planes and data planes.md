when using an API gateway for example, there is a configuration endpoint which is used to configure the API gateway and manage stuffs
the API gateway is also responsible for handling user requests
these two are different functionalities that the API gateway has to perform which can be divided into two separate planes such as the data plane which handles the user request and the control plane which manages the configuration
now the data plane can be scale separately than the control plane because the control plane doesn't need to scale too much 
also the requirements of the gateway between management and handling user request is different, example, the gateway needs to prefer availability and performance over consistency for routing requests to internal services, it should prefer consistency over availability for requests sent to the management endpoint

hence data plane -> requires performance and availability more than consistency 
		control plane -> requires consistency more than anything because of how critical the configurations are for the health of the system 

the data plane must be designed to withstand control plane failure and avoid hard dependency between them 
even if the control plane is temporarily unavailable, the data plane should continue to run with a stale configuration rather than stop, which is known as static stability

## scale imbalance

the data plane can overload the control plane due to some faulty program which can bring down the entire system down. how do we void the data plane overloading the control plane?
1. we could use a scalable file store like s3 or azure storage to as a buffer between the control and the data plane. the control plane dumps its configuration into the file store and the data plane reads from this store rather than the control plane. but this approach comes the with problem of higher latency and weaker consistency guarantee because it takes time to propagate changes from the control plane into the file storage
2. another approach is to have the data plane connect to the control plane, but have the control plane push the configuration to the data plane whenever there is an update rather than having for the data plane to periodically poll the control plane for updates
3. there is also a problem when the data plane all restart at the same time and create a huge request spike at the control plane. this can be handled by using the data store introduced earlier to defend against bulk request and let the control plane to send small deltas to the data plane whenever there is state change

## Control theory

another way of thinking about data plane and control plane is as follows: control plane is responsible for creating a controller than monitors a dynamic system, compares its state to the desired one and applies a corrective action to derive the system closer to the desired state
