The DBMS assigns each logical tuple a unique record identifier that represents its physical location in the disk

The record ID is a combination of different things based on different DBMS implementation. 
Some system can have the combination of
file no + page no + slot no

some system can have the combination of only 
page no + slot no

this makes sure that even if the tuple inside the page moves, we have an indirect layer (pointer) which is our slot no that points to the starting location and size of our tuple. this helps if our tuple changes location physically and the slot number updates accordingly which means the page id does not change even if the physical location of the tuple itself changed

inserting a tuple
- lookup the free space info in the page directory
- if free space available then check the page header to find the starting location of the free space and add the new tuple
- created a new entry in the slot array pointing to the new tuple
- update the free space pointer accordingly

updating a tuple
- check the page directory to find the location of the page
- retrieve the page from disk if not in memory
- check the free space pointer for free space availability
- if size of the update is same or smaller than the available space then update the tuple in place
- if the size of the update is larger then available space then add a deletion marker of the updating tuple and create a new page and new tuple entry in the new page

Problems with this approach
- without compaction the data is fragmented a lot i.e there are a lot of free space available between the tuples
- the DBMS must fetch the entire page even if it wants to updates a single tuple inside a page since page is the smallest unit of operation for a disk
- if the tuples are spread across different pages then we have to perform multiple random IOs to update all the tuples

the main problem here is write amplification where if we wanted to read or write a small amount of data then we still need to bring the entire page typically 4KB to 8KB of page at a time. we are doing a lot of computation to read and write these big size pages which are mostly empty inside


To solve this problem, we can use a different way to store tuples inside a page called the [[log-structured approach]]
