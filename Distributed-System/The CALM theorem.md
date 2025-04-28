how to tell whether an application requires coordination such as consensus or not 
the CALM theorem states that a program has a consistent, coordination-free distributed implementation if and only if it is monotonic

CALM -> consistency as logical monotonicity
a system will be eventually consistent if they are monotonically incrementing operations

monotonic -> new inputs refine the output, operation that only goes forward and never backwards, like adding and item into a list without removing the previous item and such. the output cannot return back to any prior output
non-monotonic -> here the new input retracts the prior output i.e removes, overwrites the output. like assigning a variable a new value

why monotonic program can be consistent, available and partition tolerant all at once?
because in the face of partition, the replicas can still accepts writes and be available and eventually those writes and will reach an consistent state

CALM focuses on the consistency of the program’s output, what does this mean?
-> this means that unlike linearizability which requires every read and write to return the most recent data, this is not the focus of CALM, CALM says that it doesn't require every reads and writes to happen in the real time order but requires the program produces the same final output, no matter the timing and ordering of input and despite any conflicts 

