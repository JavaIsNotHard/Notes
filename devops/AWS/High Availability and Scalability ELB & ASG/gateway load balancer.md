mainly used for security and inspection appliances

appliances = network security or traffic processing system that inspect, filter and modify packets

they are not part of AWS managed services but rather they are services or softwares that run inside the EC2 instance

example appliances includes:
1. firewall
2. IDS
3. proxies that inspect inbound/outbound traffic
4. and more

Gateway Load Balancers are used to manage, deploy and scale these 3rd party appliances

operates at layer 3 (network layer) and has the following functions:
1. act as a single entrypoint and exitpoint for traffic
2. then distribute traffic between all the appliances managed by the GWLB

it uses the GNEVE protocol on port 6081