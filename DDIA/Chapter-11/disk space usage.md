- uncontrolled logs can take up the entire disk space 
- to prevent this, the log is divided into segments such that from time to time it deletes old segments 

- log based also uses fixed sized buffer called circular buffer which deletes old segment from the log when it reaches a certain threshold of size 
- the messages are deleted from the head of the log such that new logs can be appending from the beginning of the log 

- in case of a slow consumer whose consumer offset points to a deleted segment will miss processing those messages

- for a hard disk with 6TB of storage and a 150MB/s write throughput it takes 11 hours to completely fill the hard disk 
- this means that the log can buffer 11 hours worth of messages until old segments get deleted.`

- 