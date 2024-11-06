Since after compaction the size of segments are small, we can merge two or more segments in a single segment while removing the previous segments to reclaim disk space.

![[Screenshot 2024-10-19 at 08.48.50.png]]

Log-structured storage never modifies the file since it is append only, so the merged segment is written to a new file.