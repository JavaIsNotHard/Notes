analytic queries use time windows such as "the average over the last five months or last five years" and so on 

in batch processing, the time when the event occurred has nothing to do with the time at which the process ran 
using timestamp in batch processing to be deterministic i.e for the same set of input it will produce the same set of output

how?
batch processing uses timestamp to identify each event i.e the time when the event actually occurred before reaching the broker or the consumer for processing
suppose we used processing time in batch processing then what happens is the output depends on when the process was ran which will yield different result in different time. so for an operation such as "average for the last 5 minutes", at 12:00 the result could be something and at 2:00 the result could be something else 
but if we used timestamps of when the event occurred, they are fixed and doesn't depend on the current time which results in deterministic output

but many stream processing system uses processing time or the processing system's local time to determine the time window. this has the advantage that it is simple to implement if the delay between the processing time and the event creation time is negligibly short but it starts to break down if there is a significant different between the two 
### event time vs processing time 

there are many reasons for the different in the event creation time and the processing time, some includes: queueing, network faults, performance issue leading to contention in the message broker, restart of the consumer, reprocessing of the events 

messages delays cause unpredictable ordering of messages so stream processing algorithms must be accommodate with such timing and ordering issues 


### knowing when you are ready 

in stream processing, you can never be sure you have received events for a particular time window or whether those events are still to come

In most aggregation based processing such as process all the request per minute of this hour, we define a fixed time window such as per minute 

let's say you want to aggregate events that happened in the time window of the 37th minute of the hour, here how do we know when the 37th events started and when they ended in the system 

suppose we move to process 38th and 39th minute of the hour, but before that we can timeout and declare the window ready after you have not seen any new events for a while, but it could still be that some events are buffered in other machine and have not arrived in the consumer yet due to several network problems. The events that arrive at a different time window than its specified time window is called a straggler event. Suppose a event with timestamp 37 arrives at the time window of 38 and 39 then they are straggle events. 

How do we deal with such straggler events?
1. one option is we can just ignore those events entirely since they are probably small in number, you can also track the ignore events as metric such that if they pile up to exceed a certain threshold then we send an alert message to the admin 
2. another option is to create a new corrected version of the data by including the straggler events and recomputing the output again for the new events

we can also use special messages called "watermarks" whose job is to tell "from now on there will be no messages with timestamp less than t"
this watermark helps us safely close all windows up to time t assuming no more late events will arrive before that time 
once the window is closed then we can start the processing of that time window 
there is also a problem if multiple consumers have their own watermark which means tha teach consumer needs to keep track of them individually 


### whose clock are you using?

this deals with whether to use the client ends device's clock or the server's clock to assign timestamp to the event time of an event 

suppose in a mobile application that sends metric over the network every interval of time. the mobile can buffer new updates in local storage until the network is available and send them over then network when  a connection is available. when we send these events then they are identified as [[straggler events]] which arrive out of order into some other time window

we can assign the timestamp for a event with the physical clock time of the client's device but the problem is that the client's device is not trustworthy because they can be manually changed making the ordering of the message bad. 

instead we use 3 different timestamps
1. the timestamp of the event when the event happened in the client side
2. the timestamp of the event when it was sent to the server 
3. the timestamp of the event when the server receives the request from the client

from here we get get a estimated timestamp as follows where estimated time is
here, 
t1 = timestamp of the event when it happened 
t2 = timestamp of the event when it was sent 
t3 = timestamp when the server received the request
t3 - t2 = offset between the client and the server or the time taken for the request to reach the server
estimate time : t1 + (t3 - t2)
