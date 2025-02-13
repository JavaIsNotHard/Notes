- a unique identifier used by the server which represents a file or a directory on a remote server 
- this is composed of 3 components:
	- filesystem identifier (volume identifier)  -> which FS the request refers to or where inside the FS the data resides 
	- filesystem inode  -> the location of the file within the FS 
	- generation number -> ensures that an old file handle cannot access a newly created file the same inode (because the previous file in the inode was deleted). whenever an inode for a file is created then a corresponding generation number is created (default value of 1) and if the OS reuses the same inode to create a new file then the generation number is incremented again. when an old file handle request is send for the same inode then the server identifies that the request is for a file that is deleted and the request is not permitted 
	