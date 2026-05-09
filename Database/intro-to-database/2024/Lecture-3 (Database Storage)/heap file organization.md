unordered collection of pages with tuples that are stored in random order

suppose in page 1 we have tuples with id 1, 2, 3 and 4 and after some time there can be a scenario where if we insert tuple with id 100, 103, 1011, 10012 they can be inserted into page 1 as well which means that tuples are not ordered based on the application level ordering of data

the database must perform these operations on the files
create, get , write and delete

the data within a page are stored in random order, so how does the DBMS know where our data actually lives at?

to get a page from a file we can perform this operation

page offset = page no X page size (find where the page is at)
size page size is consistent and fixed, knowing the page number will be enough for us to get the page offset

![[Pasted image 20260505184003.png]]

But what if there are multiple files?

![[Pasted image 20260505184038.png]]

for that we have something called a page directory which translates the page request to the location of the page on disk

page directory basically performs a hash to map the page number to the file number and then use same formula as before to compute the page offset
page offset = page no X page size (find where the page is at)

![[Pasted image 20260505184342.png]]

[[Page Directory]]