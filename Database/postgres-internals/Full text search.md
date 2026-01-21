postgres uses something called `tsvector` and `tsquery` for full text search 

this is used to search for words that are present in the entire table

### how does tsvector and tsquery work??

tsvector = postgresql's data type

```
SELECT to_tsvector('english', 'The quick brown foxes jumped');
```

this returns a result as follows

```
'brown':3 'fox':4 'jump':5 'quick':2
```

the following actions took place:
- normalization of words (stemming)
- stop words removal
- position tracking: each lexeme has numbers showing where it appeared
- sorted: each lexeme are alphabetically ordered
- duplicates merged: two lexes with the same word are merged as once lexeme with two positions

