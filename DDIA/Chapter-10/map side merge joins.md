- the idea is similar to reduce side sort merge joins
- here the input datasets are not only partitioned in the same way but also sorted based on the same key
- now the same merging operation can be performed like in reduce sort merge join by incrementally reading both input files in order and matching records with the same key

- a prior map reduce job brought the input dataset into this partitioned and sorted form