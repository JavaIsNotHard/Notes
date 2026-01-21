normal index scan:
1. scan the index to find all matching entires
2. for each matching entries, fetch the heap tuple using its row id
3. this means N random heap access because rows in heap are stored in random location

not effective. So the solution is to use Bitmap scan
uses two phase approach
1. Bitmap index scan
	1. scan through the index finding all matching entries
	2. extracts the row id (page number + tuple offset) from each index
	3. builds an in memory bitmap of heap pages that needs to be read
	4. bitmaps are page numbers not individual row location
2. Bitmap heap scan
	1. take the bitmap of page number
	2. sort them in physical location order
	3. read heap pages sequentially in ascending page order
	4. for each page, extract all rows that match the condition