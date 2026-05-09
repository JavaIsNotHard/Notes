Fixed size block of data within a file

in enterprise systems, multiple files with different page sizes 

a page contains tuples, metadata, indexes and log records 

typically a single page will contain tuple or record of a single database table

self contained pages, all the information to access the page is found within the page 

each page has its own page id which is responsible for uniquely identifying a page within a file, a disk or a DBMS

different notions of pages in DBMS:
1. hardware level (4KB) atomic writes
2. OS page (4KB , huge pages -> 2MB or 1GB)
3. Database pages (512B-32KB)

huge read traffic -> huge page size -> more data within a single fetch
small writes -> small page size


[[Page storage architecture]]