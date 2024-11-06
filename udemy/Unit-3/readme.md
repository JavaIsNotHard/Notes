# relationship between tables and schemas 

### what are the various resources or tables that a particular database or an application might need 

Relationship or ownership between various tables or records in a database. 

# Creating a database design for a photo-sharing application

## different kinds of relationship among records or tables

### one to many relationship (a user has or can have more than one photo)
Examples of one to many relationships: 
1. one boat and many crew members rowing the boat
2. one school and many students studying in the school
3. one company and many employees working in the company

### many to one relationship (a photo has one user or many photos belong to one user)
Examples of many to one relationship would be the exact opposite of that of the one to many relationship such as: 
1. Many members rowing one boat
2. Many students studying in one school
3. Many employees working in one company

### many to many relationship 
Examples of many to many relationship:
1. There are many movies in which many different actors and actresses work in 
2. There are many tasks in which many different engineers work to finish it
3. There are many students playing in many different sports  

### one to one relationship
Examples of one to one relationship:
1. one boat has one captain
2. one school has one principal
3. one company has one CEO

## For our example case we have taken three records or tables that we created which includes 
- users
- comments
- posts or photos
- likes

## We are trying to find the relationship between them 


## New terminologies used 
- Primary key and foreign key 

### Primary keys 
- Each rows in a table has their own unique primary key
- No other rows in the same table can have the same primary key
- 99% of time they are called 'id'
- primary keys are either an integer or an UUID (random combination of letters and integers but are unique to each row)
- primary keys of the row will never change. 

To create a primary key inside SQL, we use the `serial` keyword along with `primary key` keyword such as `id SERIAL PRIMARY KEY` where `serial` will give us a new number for each entry on the table and `primary key` keyword gives us some performance benefits when we are trying to lookup users using the id.

### Foreign key 
- They are not unique like our primary key 
- Different records or different rows can have same primary key 
- They are identifiers of another table and are used to generate some kind of relationship between the given table and the table the foreign key is linked with

## Data Consistency
There are 3 cases which arises when we insert values in the photos table. 
- We insert a photo that is tied to a user -> Then everything is ok
- We insert a photo that refers to a user that doesn't exist -> Then the database gives an error
- We insert a photo that is not tied to any user and is a standalone photo -> We put a NULL value to identify that the user_id is nothing.

What happens when we delete a record that is referenced by a foreign key in another database (there are some deletion constraints):
- ON DELETE RESTRICT -> Give error (`user_id INT DEFAULT 1 REFERENCES users(id) ON DELETE RESTRICT`)
- ON DELETE NO ACTION -> Give error (`user_id INT DEFAULT 1 REFERENCES users(id) ON DELETE NO ACTION `)
- ON DELETE CASCADE -> delete the items from both the main table and the referencing table  (`user_id INT DEFAULT 1 REFERENCES users(id) ON DELETE CASCADE`)
- ON DELETE SET NULL -> delete the record from the main table but set the values of the referencing foreign key as NULL rather than deleting the whole record itself. (`user_id INT DEFAULT 1 REFERENCES users(id) ON DELETE SET NULL `)
- ON DELETE SET DEFAULT -> For this we have to give the column or the foreign key a default value such that on deletion on the referencing record the foreign key gets default value. (`user_id INT DEFAULT 1 REFERENCES users(id) ON DELETE SET DEFAULT `)
