also called "network origin of VPC"
the access point is configured to accept requests only from within a specific Amazon Virtual Private Cloud (VPC) — it rejects anything coming from the public internet or outside that VPC.

When creating an access point, you choose its network origin:
1. Internet
2. VPC

The access point is only accessible with S3 VPC endpoint. Why??
Without an S3 VPC endpoint in the VPC:

- Your EC2 instances, Lambda (in VPC), ECS tasks, etc., have no private route to reach the access point's DNS name.
- Even if DNS resolves (which it might not properly), the traffic would try to go over the public internet → S3 sees it as **not from the VPC** → rejects the request