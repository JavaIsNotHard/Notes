# Implementing a Hashtag feature

We can have a hashtag table with all the hashtag that have been created
Then we can have another table that points to the hashtag id as well as the post id which helps to identify which hashtag has been used in which post
The reason we do not use a table containing both the hashtag and the post id is because there would be repetition of hashtags for each post. For example posts with post id 1, 2 and 3 might have the hashtag "Hey" which means that they tag "Hey" has to be stored in 3 different locating in the table. Now if we were to use the first concept in which we have hashtags in a different table then they are now not repeated and so the table containing the post id can point to a single hashtag for each post 


# Adding more features to the user table 

A common strategy is to make a phone number of type VARCHAR. This is because, we really don't have to perform any kind of arithmetic operation using the phone number, we just want to be able to display the number or just store the number of validate the user using the phone number. Also one single record of VARCHAR takes less space than a single record of INTEGER.


# Why adding followers and following and no of posts in the same table not good

The natural way to implement a followers and following and show the numbers in to have a column that is of type INTEGER and that is it but there is more to it then that. How about having a separate table for followers, following and posts where each of those table will have a user id associated with whom they follow and who are following them
