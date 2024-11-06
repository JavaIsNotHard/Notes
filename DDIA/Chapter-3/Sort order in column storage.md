Rather than sorting each column independently (which would make us no longer able to reconstruct the original row back), we have to sort an entire row at a time. What does that mean?

From a row we, choose a column to be a sort key.
![[Untitled-2024-10-21-0758.png]]
We can extend this idea by have more than one sort key and then sorting each sorted column is a separate database since we are already using database replication in high performance distributed systems.