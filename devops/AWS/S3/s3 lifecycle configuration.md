moving s3 objects between different access tiers

![[Pasted image 20260306133030.png|461]]

this can be either done manually or can also be done automatically using lifecycle rules

### lifecycle rules
- transition actions : this works with transitioning objects between different storage class
- expiration actions : this configures objects to expire after some time
- the rules can be created for a certain prefix within a bucket rather than to a whole bucket such as s3://mybucket/somefolder/*

You **can** move non-current (older) versions to cheaper storage classes using **S3 Lifecycle Policies**
```
{
  "Rules": [{
    "Status": "Enabled",
    "NoncurrentVersionTransitions": [{
      "NoncurrentDays": 30,
      "StorageClass": "GLACIER"
    }]
  }]
}
```

common pattern is as follows:
1. Enable versioning
2. Set a lifecycle rule to transition **noncurrent versions** to Glacier or Deep Archive after N days
3. Set another rule to **expire noncurrent versions** after a longer period (e.g., delete them after 90 days)

### S3 analytics 

runs analytics over our s3 objects and presents a analytic csv file that gives recommendation for object lifecycle transitions
