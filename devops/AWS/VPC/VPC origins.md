CloudFront feature that allows you to point CloudFront distribution directly at a resource inside a private VPC

traditionally, for cloudfront to directly traffic to other VPC resource, we had to make those VPC resources publicly available, which is undesirable because we want only our resources to be accessible through the cloudfront distribution

This is what VPC origins allow
```
User → CloudFront → (private AWS network) → Private ALB/EC2 inside VPC
```

Your origin resource:
- Has **no public IP**
- Is in a **private subnet**
- Is **not reachable from the internet directly**
- Only CloudFront can reach it, over AWS's private network

How it works?
1. You create a **VPC Origin** in CloudFront, pointing to the resource inside your VPC
2. CloudFront provisions **ENIs (Elastic Network Interfaces)** inside your VPC subnets
3. When a request comes in, CloudFront routes it **through those ENIs** directly to your private resource
4. Traffic never touches the public internet