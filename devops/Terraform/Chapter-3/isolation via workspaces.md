we use the `terraform workspace` to create isolated workspace to work with

the default workspace name is `default` and all changes are done in the default workspace

if we want to isolate configuration based on workspace then we would define separate workspaces using the `terraform workspace list` and `terraform workspace new <workspace_name>` command

how does this work under the hood?

if we have configured S3 as a backend then it would create a new folder called env inside the root of the bucket followed by another folder named after the workspace and inside which contains the state file of a particular workspace

which basically means that separate workspace files are stored in separate folder named after the workspace itself inside the env root folder

when we switch to a new workspace then it will use a different .tfstate file

### Drawbacks of using workspaces

1. the state file for all the workspaces are stored in the same backend i.e the same S3 bucket which means the same authentication can access control of all workspaces 
2. workspaces are not found defined inside code level but only when we enter `terraform workspace list` command which could confuse us if we aren't careful and deploy changes to unwanted workspaces

better option would be to use [[isolation via file layout]]