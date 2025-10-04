- the high level of docker engine
- interprets all the docker commands that user provides and asks the [[runc]] tool to perform the needed low level operation
- the docker daemon communicates with containerd via a CRUD-style API over gRPC

