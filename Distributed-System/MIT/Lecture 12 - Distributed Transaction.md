- concurrency control
- atomic commit


why distributed transaction?
- because data is split in different servers 
- hide the complexity that the data is split between multiple servers 


we package together concurrency control and atomic commit in an abstraction called transaction i.e txn provides both concurrency control and atomic commit

