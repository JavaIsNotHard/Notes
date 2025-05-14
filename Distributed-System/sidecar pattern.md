in this pattern the application program as well as a separate proxy process is running in the same localhost

the idea is that all the functionality such as routing, load balancing, observability, monitoring are delegated to the sidecar which in this case is the separate reverse proxy running in the same localhost as the main application code 

this is mainly used in microservice pattern which is deployed using kubernetes, a kubernetes pod container a container as well as the proxy service running locally side by side. All the service to service communication has to pass through the service's local sidecar service 