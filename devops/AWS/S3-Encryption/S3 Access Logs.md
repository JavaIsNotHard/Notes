![[Pasted image 20260312213814.png|126]]

- any activity that happens in the main bucket will be logged to the logging bucket
- the bucket can then be analyzed using analyzing tools 
- the target logging bucket must be in the same region as the original bucket


WARNING!!!
do not set the logging bucket as same as the original bucket. It creates a logging loop