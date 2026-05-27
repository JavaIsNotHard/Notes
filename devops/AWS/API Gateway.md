why API gateway


serverless architecture : REST API backed by lambda

HTTP : expose HTTP endpoint in the backend, basically handle HTTP requests which cannot be done using NLB

AWS service: expose any AWS API using through API gateway


API gateway - Endpoint Types

- edge optimized : API gateway deployed at the edge (improves latency)
- regional : for clients within the same region