if we take a fact table for example which contains 100 columns or more but since most transactions only care for about 4, 5 columns, the query has to retrieve all 100 columns of a row in memory, apply the condition on which columns to keep and then discard the rest. this approach is inefficient in that we have to retrieve a lot of columns for just few of them    


so instead of storing them as rows, we could store columns that belong to the same group in the same place like we store rows in a continuous manner

Storing data in column oriented fashion has the advantage of better compression using the technique of [[bitmap encoding]]