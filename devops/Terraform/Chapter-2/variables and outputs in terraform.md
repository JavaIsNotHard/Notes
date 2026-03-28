```
variable "server_port" {
  description = "The port the server will use to serve HTTP request"
  type = number
}

output "public_ip" {
  value = aws_instance.example.public_ip
  description = "The public IP address of the web sever"
}
```
then we can reference the values as follows
var.server_port 
and ${var.server_port}

```
variable "list_example" {
	description = "An example of a list in Terraform"
	type = list
	default = ["a" ', "b", "c"]
}
```

```
variable "list_numeric_example" {
	description = "An example of a numeric list in Terraform"
	type = list(number)
	default = [1, 2, 3]
}
```

```
variable "object_example" {
	description = "An example of a structural type in Terraform"
	type = object({
		name = string
		age = number
		tags = list(string)
		enabled = bool
	})
	default = {
		name = "value1"
		age = 42
		tags = ["a", "b", "c"]
		enabled = true
	}
}
```