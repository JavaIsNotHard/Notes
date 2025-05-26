
locks vs latches 

locks are different from what we normal consider locks in operating system. in database locks are higher level construct that helps us protect database abstractions such as rows, tables or even the entire database. They help in preventing multiple transaction from accessing the same resources at the same time maintaining consistency in the database

latches on the other hand are a construct that help protect lower level database resources such as disk pages that are in memory from being accessed by multiple threads at a time basically protecting the critical section of the database operation.


There are various ways that we can implement latches in database, some includes
1. blocking OS mutex or futex
2. Test and set spin latch
3. reader writer latch