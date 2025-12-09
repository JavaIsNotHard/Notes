
in configuration management tools:
- we instruct chef to install a new version of openssl
- it will run the software update on your existing server
- each server builds up a unique history of changes
- as a result each server becomes slightly different than all the others leading to subtle configuration drift bugs that are difficult to diagnose

in provisioning tools:
- we instruct the server templating tool such as docker to create a new image with a new version of openssl 
- docker creates a new image and we deploy the image across a set of new servers
- then terminate the old servers
- deployment uses immutable images on fresh servers which reduces the likelihood of configuration drift bugs
- now this means the image that was tested in dev environment is going to behave the same way in the production environment