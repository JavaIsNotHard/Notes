why RDS over deploying our database engine on EC2 instance

- auto scaling (both horizontal and vertical)
- automatic version upgrades and OS patching
- automatic backups and restore to specific timestamp
- read replicas for improved read performance 
- multi AZ support for disaster recovery
- monitoring dashboard


if we didn't use RDS for our database engine and deployed the database engine manually in the EC2 instance then we would have to manually setup all these in our instance

one of the key point that we miss with RDS is that we can't SSH into our database instance

### RDS - Storage Auto Scaling

This feature allows our RDS database instance to automatically scale when a certain storage threshold is reached or about to reach

for this, we have to define a maximum storage limit which is the storage limit of our current DB instance

RDS monitors the available free storage in the instance and when the free space drops below a threshold:
- RDS automatically increases the storage
- with no downtime

RDS triggers scaling when **both conditions** are met:
- Free storage < **10%** of allocated storage
- Low storage condition lasts **at least 5 minutes**

Then RDS increases storage by:
- **10% of current size**, or
- **5 GiB**  
    (whichever is greater)

Self managed RDS database don't provide SSH connection into the EC2 instance that hosts the database server for us

[[RDS Read Replicas & Multi-AZ]]
[[RDS Custom]]
[[Amazon Aurora]]
[[RDS Configuration Options]]
[[Backups and Monitoring]]
[[RDS Security]]
[[RDS Proxy]]
[[Amazon Elastic Cache]]
