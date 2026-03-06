
CloudFront Origins : backends that we connect our CloudFront to i.e resources of services which will be cached by our CloudFront server

**CloudFront Origin** is the source of truth for your content. It is the place where your original, definitive files are stored.

When a user requests a file through CloudFront, and that file is not present at the edge location, CloudFront goes to the origin server to grab that file, serve that to the user and the save a copy in the CloudFront server

Files are cached for a TTL

S3 bucket
- connect between S3 and CloudFront secured using Origin Access Service (OAC)

VPC origin
- for application hosted in VPC private subnet

Custom Origin
- any HTTP server that CloudFront can reach over the internet
- any public HTTP backend you own