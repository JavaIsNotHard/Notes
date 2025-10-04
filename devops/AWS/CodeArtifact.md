a secure container to place all external dependencies, libraries and packages 
benefits of using code artifacts:
1. security
2. reliability
3. control

upstream repository are those repositories that are used when the code artifact itself fails or when the code artifact does not have the packages needed it pulls it from the upstream repository

if we are serving the application from an EC2 instance then we need to configure proper IAM role that grants all the required permissions to the EC2 instance

```
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "codeartifact:GetAuthorizationToken",
                "codeartifact:GetRepositoryEndpoint",
                "codeartifact:ReadFromRepository"
            ],
            "Resource": "*"
        },
        {
            "Effect": "Allow",
            "Action": "sts:GetServiceBearerToken",
            "Resource": "*",
            "Condition": {
                "StringEquals": {
                    "sts:AWSServiceName": "codeartifact.amazonaws.com"
                }
            }
        }
    ]
}

```

the following configuration is used to allow ec2 instance to access the codeartfiact service
- "Effect": "Allow" means that this statement grants permission.
- "Action" lists the actions that are allowed. Here, it includes:
    - "codeartifact:GetAuthorizationToken" allows getting an authorization token for CodeArtifact.
    - "codeartifact:GetRepositoryEndpoint" allows retrieving the endpoint for a CodeArtifact repository.
    - "codeartifact:ReadFromRepository" allows reading packages from a CodeArtifact repository.
- "Resource": "*" means these actions are allowed on all resources (*) in CodeArtifact. In a production environment, you would typically restrict this to specific resources for better security.

- "Effect": "Allow" means this statement grants permission.
- "Action": "sts:GetServiceBearerToken" allows calling the GetServiceBearerToken action from the AWS Security Token Service (STS).
- "Resource": "*" means this action is allowed on all resources.
- "Condition" adds a condition to this permission.
    - "StringEquals" is a condition that checks for string equality.
    - "sts:AWSServiceName": "codeartifact.amazonaws.com": This condition ensures that the sts:GetServiceBearerToken action is only allowed when the AWS service name is codeartifact.amazonaws.com. This is a security measure to restrict the use of this STS action specifically for CodeArtifact


the IAM policy must be associated with an IAM user which gives our EC2 instance the required access permissions

 **💡 What's the difference between a policy and a role?**  
 Think of a **policy** as the actual list of permissions - it's a document that specifies exactly what actions are allowed or denied on which AWS resources. For example, "allow reading from this S3 bucket" or "allow publishing to CodeArtifact."
 
 A **role** is the container that holds these policies and can be assumed by users, applications, or AWS services. You attach policies to roles, then assign the role to whoever needs those permissions.
 
 This separation is powerful because:
 
 - You can attach the same policy to multiple roles
     
 - A role can have multiple policies attached
     
 - You can modify a policy once and affect all roles using it
     
 Roles can be assumed temporarily, while policies define the permanent permission boundaries