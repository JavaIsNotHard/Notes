- make a backup (snapshot) of the EBS volume at a point in time 
- not necessary to detach volume when creating snapshot from the instance but recommended to do so
- we can also move snapshots between AZ which allows us to restore a volume of one AZ to another

## EBS Snapshot features
- EBS snapshot archive 
	- move a snapshot to "archive tier" that is 75% cheaper than the "standard tier"
	- takes 24 to 72 hours to restore an archived snapshot
- Recycle bin (retention rule)
	- protect resources when they are deleted (accidentally or on purpose) for a fixed retention period
	- only 3 resources can be moved to recycle bin -> snapshots, volumes & AMIs
- Fast Snapshot restore
	- restore a snapshot as fast as possible

when running snapshots or taking backups, we shouldn't run them while your application is handling a lot of traffic because backups use IO as well