like Chef, puppet and ansible are configuration management tools which are used to design and install and manage software on existing server

advantages of using configuration management tools over ad hoc scripts:
1. code convention: there is a systematic way to define the steps to setup the server
2. idempotence: making sure that executing the same script multiple times ensures same result is hard, making sure that a folder is deleting before the script is ran again and dealing with these small nuances is hard. code that works correctly no matter how many times we execute it is called code idempotence 
3. distribution: ad hoc scripts are meant to be ran on a single server whereas configuration management tools are ran in different servers at the same time