similar to how inputs files are immutable in batch processing, the same idea of immutable event log makes event sourcing and change data capture powerful 

database store the current state of the application, the nature of state is that it changes over time through updates and inserts, and does this fit into immutability?

state changes over time because there were a sequence of events that caused those changes to be made i.e the current state of the system was reached because there were events that mutated the state over time. example, the currently available seats in a restaurant is due to the events that booked the seats 

mutable states like database and immutable event logs coexist with one other and requires one other for a system to perform well. a current mutable state can only be derived by reconstructing the snapshot of the current state by replaying the event log 

the log of all changes i.e the changelog, represents the state of the system over time, if you store the log durably then it makes the state of the system reproducible. we can think of the log as our source of truth and system or record whereas our mutable state like database or other derived system as a cache to hold the latest record values of the log 

[[advantages of immutable events]]

[[deriving several views from the same event log]]