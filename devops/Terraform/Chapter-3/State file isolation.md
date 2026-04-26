we could define all our infrastructure code inside a single state file or .tf file

we might need functionality that separates different envinronments (dev, stage & prod). changes to dev could affect staging and prod env because all the changes happen in a single file

so we need to isolate the state files for each envs. terraform allows you to do this using two techniques:
1. [[isolation via workspaces]]
2. [[isolation via file layout]]