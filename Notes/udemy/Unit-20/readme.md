# Implementing schema into postgresql 

```sql
SELECT email 
FROM YourTable 
WHERE email NOT LIKE '%_@__%.__%'
```

This will ignore the following cases (simple version for valid emails):

- emails that have at least one character before the @;
- emails that have at least two characters between @ and .
- emails that have at least two characters between . and the end.

`ALTER TABLE your_table ADD CONSTRAINT chk_email CHECK (email LIKE '%_@__%.__%')`

# Rules of validation 
- If the rules around validating the value might change frequently then no validation(validation done by the backend server in use)
- If rules around validating the value are complex then no validation (validation done by the backend server in use)
- If the values are in a definite range and will not change then we can use database validation for example checking whether a number is greater than 10 or NOT


