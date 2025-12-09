alternative to configuration management tools such as chef, puppet or ansible

instead of launching a bunch of servers and running the same code on each one, the idea behind server templating is to create an image of a server that captures a fully self-contained "snapshot" of the operating system

here the servers are immutable because the image we use is build on the same snapshot, if we need changes then we deploy a new image and kill the old the one

