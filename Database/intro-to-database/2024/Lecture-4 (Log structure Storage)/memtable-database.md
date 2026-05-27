A memtable is basically an in-memory data structure, it can be anything that ranges data in a sorted and search effective manner

All the writes in the LSM storage goes to the in memory memtable first

the data inside the memtable must be

fast to insert

fast to lookup

sorted

this rules out hashmap because they are not ordered and the most common implementation is skiplist

memtable acts as a write back cache where new data are only inserted into the cache first and then the write to disk is deferred later

what are the entries in the memtable

key : uniquely identifying key

sequence number : monotonically incrementing counter

type : type of operation (either PUT or DELETE)

value : the value we are storing

write path

every new write first goes to the WAL which appends the new log record and then flushes it in the background sequentially  
and once the WAL is updated successfully is the skiplist also updated accordingly  
this WAL is only needed until the skiplist's leaf node is pushed to disk

read path

every read first goes to the memtable, if no result found then it goes to different levels in SStables

after the memtable threshold is reached then the current memtable in memory is made immutable i.e no new entries can be appended to this SkipList

a new memtable is created to allow new incoming writes

background thread flushes the immutable skiplist to disk (sstable) by iterating the leaf node of the skiplist, once complete the sstable is made immutable

WAL entry covered by this flush is removed

the immutable memtable is garbage collected and freed from memory

flushing never blocks new writes because when the memtable is full and needs flushing, it creates a new memtable to allow new writes

[[summary table]]