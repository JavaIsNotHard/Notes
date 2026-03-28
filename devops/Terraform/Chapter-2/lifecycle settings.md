configure how the resource is created, updated or deleted

useful lifecycle setting is create_before_destroy

create_before_destroy to true, Terraform will invert the order in which it replaces resources, creating the replacement resource first and then delete the old resource