different transaction processing system i.e the system that powers the customer-facing website
since the OLTP databases are the ones that store user inputs and data they are guarded properly by database administrators and are do not allow analyst to run ad hoc analytic query on the OLTP database since those queries are expensive, scanning large parts of the dataset

A data warehouse on the other hand is a separate database from OLTP database that the analyst can query to their hearts content without affecting the OLTP database
Data is first extracted from the OLTP database, transformed into an analysis-friendly schema, cleaned up and loaded into the data warehouse. This is the ETL (extract transform load) process


![[Screenshot 2025-05-06 at 2.49.27 PM.png]]

One other advantage of using a separate data warehouse is that the data warehouse can be optimized for analytic access pattern. the index used in OLTP systems are not much useful for data warehouse access patterns

Storage engines that are optimized for analytics:

[[Schema for analytics Stars and Snowflakes]]
