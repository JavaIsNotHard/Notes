# CREATING A LIKE SYSTEM 

## Not letting same user like the same post more than once 
```sql
CREATE TABLE likes (
    id SERIAL PRIMARY KEY,
    user_id INTEGER REFERENCES users(id) NOT NULL,
    post_id INTEGER REFERENCES posts(id) NOT NULL,
    CONSTRAINT unique_post_user_liked UNIQUE(user_id, post_id)
)
```
This ensures that for each record the value of the `user_id` and the `post_id` is different.

## The Coalesce() function
This function returns the first not null value inside the function. For example we want to check if a `user_id` is present in the table the we could do something like 
`COALESCE((user_id)::BOOLEAN::INTEGER, 0)`
If `user_id` is not NULL then return the `user_id` else return 0

