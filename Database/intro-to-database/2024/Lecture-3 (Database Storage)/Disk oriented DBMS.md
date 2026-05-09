
in disk architecture or approach, the entire database is a file

some DBMS will store all the content in a single file e.g sqlite
others will store the content in separate files e.g postgresql

the files themselves are not that special in the eyes of the OS
the way the DBMS interprets this files is where the actual magic happens

files are divided into pages and the first page is the directory page
all pages are of fixed size division of the file
each page has a header within its own boundary

in memory we have a buffer pool, it contains frame which will store pages that we bring from memory

we have an execution engine which executes queries, the execution engine is also responsible for asking pages from the buffer pool

suppose we engine asks for page #2, the buffer pool looks at its frames, currently the frame is empty so it first fetches the page directory from the file into the empty frame. it looks into the page directory to find the location of page #2. once found it will fetch the page from its location and add it into its empty frame and gives a pointer to the page to the execution engine. The execution engine updates the page, reads the page, adds new item to the page. the job of the buffer pool is to safely write out the page back to disk


How the DBMS represents the database in files on disk
[[File Storage]]