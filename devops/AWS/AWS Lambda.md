lambda inside a VPC


lambda by default outside a VPC can only access resources that have publicly available URL given by AWS in creation time. this does not include those resources that are given a public domain manually by us


once the lambda is inside the VPC then it can access the resources inside the public and private subnets



one thing to note is that lambda itself is not the execution engine of our environment, lambda invokes an execution environment for our handlers to run itself. So lambda is something like a controller or an external service that watches or any invocation request of the lambda functions. if there is a new lambda invocation request then the job of the lambda is to setup the appropriate environment for the function to run at



which means that lambda inside a VPC is not the lambda service itself (lambda service is globally managed by AWS)
but the environment in which the lambda function runs in is inside the VPC, inside the private subnet etc



one of the most common access pattern is setting up RDS proxy in front of our RDS and aurora because directly hitting the RDS and Aurora instances can leave a lot of open connections due to the fact that lambdas are short lived and they spun up new environments for concurrent requests