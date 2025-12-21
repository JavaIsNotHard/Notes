
if self managed gitlab inside a private network (VPN) then codebuild cannot access the resources directly through the public network

codebuild needs to be inside a VPC which has a site to site vpn connected to the private gitlab server

