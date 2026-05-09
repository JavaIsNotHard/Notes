![[Pasted image 20260507191429.png]]

most row oriented database use the slotted page approach to store tuples inside a page

the slotted page approach contains the following component:
1. page header: contains metadata about the page such as
	- number of slots used
	- pointer to the start of free location
	- page id, checksums and more
2. slot array: contains information about the position of the tuple inside the page. the data contains. basically a pointer to the tuple. contains.
	- offset -> where the tuple starts in the page
	- length -> how long the tuple is
3. tuples : holds the actual record or the row data

the tuples grow from right to left
the slot array grow from left to right
when they both meet each other, we say that the page is full


why the slot array approach?
if you have the page number and the slot number then you can get to the tuple

how does a query know the location of a tuple? 
each tuple is represented with something called as a [[Record ID]]

