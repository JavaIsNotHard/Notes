basically a hash table 
different dbms will do different 

stored in the database header page on disk which maps logical page IDs to their physical location on disk 

a special page used by the dbms to track the location of data pages in the database file

so basically for a database object X, it helps us find where it is located at or in which file is it located at

- contains one entry per database object (tables, index and such )
- must make sure that the page directory is in sync with the data pages since it contains the location where the data resides and if not in sync then we wouldn't be able to know to go to find our data

main responsibility
- location tracking
- free space accounting and management
- page type info

the free space information can be within the page metadata or a separate file containing the free space information


[[Page Header]]