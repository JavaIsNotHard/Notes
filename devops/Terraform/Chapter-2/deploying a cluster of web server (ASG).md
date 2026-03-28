```
resource "aws_launch_configuration" "example" {
  image_id = "ami-0b6c6ebed2801a5cb"
  instance_type = "t3.micro"
  security_groups = [aws_security_group.example_sg]

  user_data = <<-EOF
  #!/bin/bash
  echo "Hello, World" > index.html
  nohup busybox httpd -f -p ${var.server_port} &
  EOF
}

resource "aws_autoscaling_group" "example" {
  launch_configuration = aws_launch_configuration.example.name
  min_size = 2
  max_size = 10

  tag {
    key = "Name"
    value = "terraform-asg-example"
    propagate_at_launch = true
  }

}
```
here aws autoscaling group's launch configuration references aws launch configuration option
ASG -> aws_lauch_config
when we want to make changes to the launch config, it needs to delete the old config and only when can it create a new one

here since ASG references the old launch config, this action is blocked
