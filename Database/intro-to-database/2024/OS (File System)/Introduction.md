two main abstraction for file systems

1. files : linear array of bytes, each file has a low level name that is associated with it which is called as the inode number
2. directories : also has a low level name called inode number, its content contains a list of (user-readable name, inode number) mapping. example, ("foo", 10)
