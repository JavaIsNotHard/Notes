each page has a page header which tell info about the page itself 

oracle stores the schema information in the page header itself. most system don't do that

what information does the page header contain:

1. page size 
2. checksum 
3. DBMS version
4. Transaction visibility
5. Compression / Encoding Metadata
6. Schema information
7. Data summary


some system requires the page to be self contained. why self contained pages?

- **Recover data** from a single page even if other pages are corrupted
- **Read/interpret** a page independently during crash recovery
- **Move or copy** pages without losing context


how the content of the page are stored inside the page?
[[page layout]]