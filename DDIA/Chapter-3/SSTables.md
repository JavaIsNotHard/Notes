SSTable stands for Sorted String Table and is an approach where our log-structured segments are sorted by their key.

This process involves reading all the input file from each segment and merging them based on the key like in mergesort algorithm. 

![[Screenshot 2024-10-20 at 08.06.39.png]]

The steps involved includes, first the first item of each segment is taken and compared with one other, the item that has the lowest key is added to the merged segment (new file).

If more than one segment has the same key then we take the key value pair of the most recent segment and discard the key value pair of older segment.

To find a particular key in the merged segment we can keep track the starting offset of one key for every few kilobytes in the segments. This is not the same as the hash-index which would require all the keys to be placed inside the index. This new approach only requires some keys for every few KB which reduces the size of the in-memory index. 

The finding process for a key involves guessing the segment where the key can be present. For example, we need to find the key handiwork, the index has the entry for the key value handbag and handsome, because of the sorted property of SSTables we know that handiwork falls between handbag and handsome so we can start scanning from handbag.

It is also possible to group records and compress them before writing them on the disk such that the index need only point to the start location of the compressed block. Compression helps with disk space management and reduces I/O bandwidth.

[[Constructing and maintaining SSTables]]