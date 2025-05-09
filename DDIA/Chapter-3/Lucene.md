How lucene uses the principle of LSM trees such as merging and compaction to get their index working

the mapping between the term or the word and the list of IDs of all the document that contains the word is kept in a SSTable-like sorted file, which is merged in the background when needed

