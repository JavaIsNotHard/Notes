how to store tuple inside a page

inside the page header we keep track of the num of pages. the starting count is 0 so a when adding to a new page, we add from the starting location. when adding new page, we move by the length of the page to find the next free location in the page.

![[Pasted image 20260507181426.png]]

this is the strawman approach and has the following flaws
- what happens when the tuples are deleted?
	- we need an addition tracking to check for free space between pages
- what happens if the tuples are of variable length?
	- here is where the main problem lies


so instead of this we use another approach called the [[slotted page]] approach