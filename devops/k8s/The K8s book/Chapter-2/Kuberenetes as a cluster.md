A cluster is basically a collection of nodes that are interconnected with each other that work as a single system 
Each kubernetes cluster has two types of nodes
1. [[control node]]
2. [[worker node]]

both [[control node]] and [[worker node]] can be physical server, virtual machine or a cloud service that runs in different architecture such as ARM and x86/64 and even different operations systems such as windows and linux

The main job of control node is to manage the nodes in the kubernetes cluster and it is preferred to be ran in a different server than a worker node i.e running the control node and the worker node in different servers which enables control node to just focus on managing the cluster 


