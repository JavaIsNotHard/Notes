
how does terraform know changes that need to be updated based on the configuration file?

for every terraform plan and terraform apply, terraform creates a terraform.tfstate file in the root of the terraform project

the terraform.tfstate file is a custom JSON file that contains information about what the state of the infrastructure is in the the AWS account associated with this particular user ID

The JSON output `terraform.tfstate` file knows about all the resources and their names and what they corresponds to in your AWS account with a particular ID

Every time you run Terraform, it can fetch the latest status of this resource from AWS and compares that to what’s in your Terraform configurations to determine what changes need to be applied

state problems when working on a team
1. [[shared storage for state information]] : each team member must have access to the most up-to date state file inorder to apply new changes

2. locking state files : avoid race condition when multiple team members run terraform apply at the same time

3. isolating state files : isolate different environments for example, testing and staging 

