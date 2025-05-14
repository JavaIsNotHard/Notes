an event by itself is not helpful for returning to the user because they don't contain any state information
For a shopping site, an event could be something like `ProductAdded(id = 123, qty=1), ProductAdded(id=456, qty=2), ProductModified(id=123, qty=2)`, and if we were to represent it as it is then we get stuff that are not useful for the user to view such as the `ProductModified(id = 123, qty=2)` event
so basically a user expected to see the current contents of their card rather than an append-only list of all changes they have ever made to the cart

instead what we can do is replay the event log and apply transformation logic to build the current state 
it can to thought of like this, write operations emit event logs whereas read operation derive state info from those logs 
the transformation logic itself must be deterministic to ensure that if we replay the event log multiple times then every time we must end up in the same state 

log compaction in event sourcing is different from log compaction in CDC

for every key, only the most recent value is kept in the log for CDC 
in event sourcing, events are modeled at a higher abstraction level such as user intent like "user clicked this button at this time" and so on. these cannot be override with prior events because the current state is constructed by replaying all the events in sequence and all the events lead up to the current state

applications can use event sourcing also have some mechanism for storing snapshot of the current state that is derived from the event log such that we don't have to reprocess the entire log to get the current state of the application

