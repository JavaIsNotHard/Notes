what is code deploy application?
what is code deploy deployment groups?

> 💡 **Why does CodeDeploy need IAM roles?**  
> **CodeDeploy needs IAM roles** to get permissions to access and manage AWS resources on your behalf. These permissions let CodeDeploy do things like:
> 
> - Accessing EC2 instances to deploy applications.
>     
> - Reading application artifacts from S3 buckets.
>     
> - Updating Auto Scaling groups.
>     
> - Write CloudWatch logs about what it's doing