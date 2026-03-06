Instead of overwriting an object with the same key, we create a new version of the file

benefits of versioning
1. safe deletion (marks as deletes i.e sets the delete flag but does not actually delete the file)
2. restore or rollback files to previous versions

when deleting a specific version of our s3 file, then we are permanently deleting the file 
when we are not deleting a specific object then we are creating a delete marker object for our to delete object which marks the object for deletion but does not actually delete the object