document model vs relational model 


document model: schema flexibility, easy scalability, better performance due to locality
relational model: transactions, joins, relations

the primary reason document model are easier to scale than relational model is the fact that joins exists in the relational model. How?

when you split data across two nodes (servers), performing a join requires **network communication between those nodes** — one node has to ask another for its data. This is:
- Slow (network is much slower than local disk)
- Complex to coordinate
- A potential bottleneck as data grows

Another reason for having less scalability is due to the fact that relational model supports ACID property


if our data is represented as a tree of many one to many relationship then document model is preferred in this case

user has many positions entries (one to many)
user has many eductions entries (one to many)
user has many contact entries (one to many)

if our application requires that all the data to be present all the time then document model is preferred

```json
{
  "user_id": "123",
  "name": "John",
  "positions": [
    { "title": "Engineer", "company": "Google" },
    { "title": "Intern", "company": "Amazon" }
  ],
  "education": [
    { "degree": "BSc CS", "school": "MIT" }
  ]
}
```

instead of having multiple tables like positions, eductions, contacts, and for the user table to have multiple foreign relationship between them, we can have a single document that contains all our data inside of it

this is the locality benefit of using document model

one major disadvantage of using document model is that fact that we cannot directly refer data that is nested

another advantage of using document model over relation model is when we have to deal with the order of items.
relational model are built around set theory where order doesn't matter, we cannot change the order of data once we have inserted them, we could using a separate order id but it would be messy when trying to add item in the middle
in document model, we can just rearrange the item without any hassle so another win for document model


### schema flexibility in the document model

document model: no strict schema requirement, schema on read so the application code is responsible to check if the structure of the schema is correct or not
(runtime check)

relational model: strict schema requirement, schema on write so when we write a new structure it must adhere to the one defined 
(compile time check)

this is noticeable when dealing with changing the format of an existing data, we can update the value of a document, we can add a new entry in the document but we cannot change the existing structure or format of the document. instead, we need to define a new entry where the old entry lives alongside of it

changing the format of the data or attribute is easy in relational model where we can delete attributes at wish and also create new attributes easily, when changing the structure of a data we need to perform an update operation for each attribute of the table.
if the table is too large then it would lock the data and would cause lock contention and hamper the performance of the database. instead what we can do is lazily update the values of the newly created attribute at read time.
the logic is as follows
```js
function getFirstName(user) {
    if (user.first_name !== null) {
        // New rows: already has the value, just return it
        return user.first_name;
    } else {
        // Old rows: derive it from the full name
        return user.name.split(" ")[0];
    }
}
```

