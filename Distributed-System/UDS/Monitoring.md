
Monitoring is used to detect failures and to trigger notification to the human operator responsible for the system

another use case of monitoring is to provide a high level overview of the system's health via dashboards 

black-box monitoring was used to report whether a service was up without much visibility of what was going on inside 

white-box monitoring is used to report whether specific features worked as expected such as whether the service was taking up a lot of resources like memory or CPU, what are the write and read throughput of the database and much more that deals with services and what's happening under the hood 


## Metrics
time series of raw measurements of resource usage or behavior where each sample is represented by a floating point number and a timestamp

time series means a sequence of data collected over time 
example of a resource usage metric could be something like this:
1. `timestamp: 10:00 | value: 65.5%` where the value indicates either CPU, memory or disk usage

metrics also measure the behavior of the system like the total number of times the system failed and so on. example
`timestamp: 10:00 | count: 1`

Metrics can be tagged with key-value pairs such as labels, an example label could be something like 
`"region": "us-east", "cluster": 4, "node": "xyz"`
this helps us to search metric by either region, cluster or node when monitoring where the problem occurred. 

One way to record activities to monitor is through the use of event-based approach, example, we could return an event corresponding to the failure of service to perform an operation, then this event is send to the local telemetry agent, the telemetry agent then batches these events and emits them periodically to a remote telemetry service which persists them in data store
this can cause the data store to use a lot of space which will make aggregation of those records or logs difficult because the logs are huge 
one way to remedy this problem is by using pre-aggregation over certain time (per minute, per hour, or per day) such that it doesn't have to aggregation everything at a single time 
`
`
we can then create multiple pre-aggregates at different time intervals this way we can choose from a list of pre-aggregates that suits the need of our query. Example of a ingestion service is AWS CloudWatch

Once the pre-aggregates are computed, we no longer have access to the original events to compute other aggregation operation. For example, if a metric is pre-aggregated over a period of 1 hour, it can’t later be re-aggregated over a period of 5 minutes without the original events.

they are usually persisted in a pre-aggregated form in a data store specialized for efficient time series storage
