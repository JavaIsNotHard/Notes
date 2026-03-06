auto backups
daily full backup at the specified time during the configuration
transactions or replication logs backed up every 5 mins
the backup retention time ranges from 1 to 35 days, we can set the value to 0 to disable backups

manual db snapshots
manually triggered by the user
the backup is saved as long as you want and until you delete the backup


even if the db is stopped, you still have to pay for the storage
so instead of stopping the db, you take the snapshot of the db which costs way less than the using the storage and delete the original db, once we want to reuse the db then we restore from our previous backup

- RDS and Aurora both have PITR (point in time restore) 
- PITR lets users to restore both RDS and to any specific second within the backup retention window (1-35 days) 
- we can only restore data within this retention period
- and the most recent point of restore with automated backup is 5 minutes of the current time since RDS and Aurora backs up the transaction log every 5 minutes

- Restoring an automated backup or manual snapshot creates a new DB instance
- You then need to point your app to the new endpoint of the new DB instance

we can use s3 bucket to store backups and snapshots
- then we create a new RDS instance and restore it 
for aurora, we create a backup using a tool called `percona xtrabackup`
- then we restore the file onto a new Aurora cluster 

aurora cloning is faster and cheaper option than taking snapshots and backups
because it uses the copy on write protocol just like in OSes


