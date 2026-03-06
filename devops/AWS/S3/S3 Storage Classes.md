different storage class for different access patterns and cost requirements

the classes are divided as follows
1. frequently accessed data
	1. s3 standard : default class. has 11 9's durability
	2. s3 express one zone
2. infrequently accessed data
3. unpredictable access data
4. archive / long term storage data


we can move objects inside s3 through [[s3 lifecycle configuration]]
