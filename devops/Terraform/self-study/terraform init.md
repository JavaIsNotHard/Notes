after creating a main.tf file for the first time, we run the terraform init command to do the following

the terraform binary does not come with the code for any of the providers e.g AWS

tell Terraform to scan the code, figure out which providers
you’re using, and download the code for them

it’s safe to run init multiple times (the command is idempotent)