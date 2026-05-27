
we can invoke lambda functions directly from RDS and aurora for data change events i.e if some data or rows or columns in the database gets modified then it can invoke the lambda with the modified data as the event


we set it up from within the database by connecting to it, not setup from the AWS console


RDS instance is the one invoking the lambda function so we have to allow inbound traffic from RDS permission in the lambda function IAM role


Also RDS itself must have proper permission to invoke a lambda function



Another way to invoke lambda from the DB instance is using event notification

the previous method was a direct invocation of the lambda function. this approach is an indirect approach

The events that lead to the trigger includes events inside the DB instance itself such as creating, stopping, restarting and starting and more. Not invoked based on data change and update events

Subscribe to the following event categories: DB
instance, DB snapshot, DB Parameter Group, DB
Security Group, RDS Proxy, Custom Engine Version

since it is indirect, we need a delivery mechanism to the lambda function. these delivery mechanisms include SNS or event bridge



