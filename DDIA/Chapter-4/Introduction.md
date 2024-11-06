- for server side application rolling upgrade or a stage rollout
- for client side application, we have to depend on the client to upgrade the application for example, an OS upgrade

When we upgrade a system, both the old format and the new format can coexist in the system at the same time. To deal with this problem we have the following measures:
1. Backward compatibility: Newer version of the code can read data written by the older version 
2. Forward compatibility: Older version needs to read data written by newer version 

- Achieving backward compatibility is easy but not forward. 
- Since older version of the code doesn't know the structure of the new data format it needs to ignore some additions made the the newer version.

## Formats of encoding
- in memory data structures such as lists, sets, trees, hash maps and such 
- structure that can be written to disk and sent over the network such as sequence of bytes that are understood universally by all types of computers

Changing one format to another format i.e from in memory to byte-sequence is called encoding, marshalling or serialization and changing the reverse is called decoding, unmarshalling and deserialization

## Language-specific formats
- java has java.io.Serialization
- python has Pickle
- Go has serialization and more

Here are the drawbacks of using language-specific formats:
- reading data using other programming language becomes difficult
- using language specific format requires the use of arbitrary instantiation of classes which deserializes the code. If an attacker an intercept the class then they can perform malicious activities with the program .
- evolvability is not kept in mind 

JSON, XML and binary variants 
- Since json data are represented in human readable format, the size of the actual data is going to be big compared to its binary variant which stores information as sequence of bytes. 

Apache Thrift and Protocol Buffer
- Binary encoding format 
- Protocol buffer is developed by google and thrift was originally developed by facebook 
- Both requires a schema definition beforehand which looks something like this

![[Screenshot 2024-10-24 at 15.46.41.png]]
Fig: protocol Buffer schema format
![[Screenshot 2024-10-24 at 15.46.36.png]]
fig: apache thrift schema format

- They both have code generation tools which translates this schemas into classes or objects of a particular programming language (interface to exchanging data)
- Apache thrift has two different encoding formats which includes 
	1. Binary protocol 
	2. Compact protocol
![[Screenshot 2024-10-24 at 15.49.04.png]]

- The first byte indicates the type (0x0b = type 11 = string), (0x0a = type 10 = i64) and so on. 
- The next two fixed sized bytes include the field tag (which is defined in the schema of the format) (00 01) indicates field tag = 1, (00 02) indicates field tag = 2 and so on 
- The next is a fixed sized length field for string types of size 4 bytes, if integer or other numeric then it will contain the actual value of the integer. 
- The next sequence of byte for string includes the actual value of the string 
- the final byte is the end of struct byte which has the value of 0x00.
- takes a total of 59 bytes

![[Screenshot 2024-10-24 at 15.49.12.png]]

- Improves upon the design of the binarycompact mode. 
- instead of representing field type and tag name as different bytes which will take a lot of space. The compact mode merges the field tag and the type into a single byte. 18 -> 0001 1000 where 0001 -> field tag = 1 and 1000 = type 8 (string)
- The next byte is the length if it is of string type if it is a numeric type then it is going to contain the value instead. 
- The next byte sequence is the value of the string 
- The final byte sequence is the end of struct whose value is 0x00.
- Encodes the same data in 34 bytes 

![[Screenshot 2024-10-24 at 15.49.19.png]]

- The fields of both thrift and protcolbuf have the required and optional keyword. 
- These are not represented in byte sequence 
- Checked by the application code, if required field then the runtime check fails if the field is not set. 

- Field tags are critical for the meaning of encoded data. 
- You can change the name of the field because the data never refers to the field name 
- You cannot change the field tag because all the data would be invalid

We can add new fields to the schema if they are assigned a new field tag
The use binary encoding provides forward compatibility, if old code (which doesn't have the updated schema) tries to read data from new code (which has the updated shcmea) then the old code can simply ignore the new field. 

Backward compatibility can also be achieved because the field tag for both the new code and old cod has the same meaning or refers to the same tag. In new code, you cannot add a new field and make it required because this would invalidate all the old code which does not have the data.

### Datatypes and schema evolution
Changing the data type of a field. This depends on the binary encoding format. If we have a 32-bit integer used in the old code and we migrate that field to 64 bit. Here two things to consider. 
1. forward compability: the 64 bit field can store and 32 bit field and pad the extra space with 0.
2. backward compatibility: this is tricky because if we migrate to a larger data type then the value may be truncate into something different.

Including `required` and `optional` we also have the `repeated` marker. 
the repeated marker says that the same field tag appears multiple times in the record. 


## Avro
Another binary encoding format used by apache hadoop to replace apache thrift
This encoding format is different from ProtoBuf and apache thrift but it also encodes data in less bytes than both of them 
We have a schema defined beforehand (Avro IDL) and a machine readable schema (JSON)
![[Screenshot 2024-10-25 at 08.05.26.png]]

![[Screenshot 2024-10-25 at 08.06.13.png]]

- we do have a field tag which identifies which field the byte sequence belongs to 
- we only have a length and a UTF-8 encoded sequence of bytes 
- To tell the type and the field  we have to know the writer's schema that was used to encode the data and compare the fields in the schema with the btyte sequence in the encoded data 

- Avro has two types of schema (reader's schema and writer's schema). The reader's schema is used by the reading node and the writer's schema is used by the writing node 
- When application wants to encode a data it needs a writer's schema 
- When application wants to decode a data then it needs a reader's schema
- The writer's and reader's schema do not have to be the same, When data is read or decoded then Avro resolves the difference between the schema by comparing the fields in both the schema and translating the data from writer's schema to reader's schema
![[Screenshot 2024-10-25 at 08.20.53.png]]

- The field that appears at the writers' schema but does not appear in the readers' schema is ignored.
- If the reader is expected some field to be present but the writer's schema does not have the field then the value is field with its default value


### Schema evolution rules 
forward compatibility -> New version of writer and old version of reader 
backward compatibility -> New version of reader and old version of writer 

- To maintain compatibility we can only add or remove fields with default value 
- we add a new filed with a default value, the reader has the new version of the schema and tries to read data written by the old version of the schema which does not have the new version, then it will fill the value with the default value set in the new schema.
- If we added a field without a default value then the new version of reader cannot read data written by an old version and hence breaks backward compatibilty.
- When we remove a field without a default value then the old reader would be able to read the new writer's version and hence break forward compatibility

- In Avro, to use a default value we need a to define a `union` type in the schema beforehand
- `union {null, string, long}` means the value can be null or string or long

### How is the schema known to all nodes 
- we know that a reader will have a reader's schema and a writer has a writer's schema but how does the reader know the writer's schema (this is needed to compare both the schema and ignore field or fill fields with default value)?
- We cannot add the schema along with the encoded data because that would remove the purpose of encoding and shortening the length of the data 
- The answer depends on the context that Avro is being used for:
	1. Large files with a lot of records: Hadoop uses Avro for for storing large files all encoded in the same schema which means the writer can include the writer's schema at the beginning of the file once and let the reader read of the same schema for all the records. 
	2. Database with individual records: Different record may be encoded by different version of the writer's schema which means only one schema is not sufficient. The solution is to add a version number before the record and keep a list of schema version in the database. So now when a reader fetches a record, extracts the version number and gets the schema out of the database it gets the exact version that the record was written by. 
	3. Sending record over the network: When two parties are communicating over a bidirectional connection then they can send the schema during the connection setup process once . 

### Dynamic schema generation in Avro
## Models of dataflow

How data flows from one process to another, how encodes the data and how decodes it?
various ways where data flows between processes includes:
1. via databases 
2. via service calls 
3. via asynchronous message passing

### Via Database 
- The process that writes to the database encodes the data and the process that reads from the database decoes the data 
- There can be multiple process accessing the database or a single process accessing the database. 
- Multiple process can either be different application running or the same instance of the service running for replication.
- Some process will be running newer code while others will be using older codes 
- This means we will have two versions of the code, if a newer version of code wrote to the database then there can be an older version of the code accessing the database. Thus, forward compatibility is required in database 

- Data outlives code. 
- A single database can contain data written by various application code through the years.
- Some data may be written 5 milliseconds ago while some may be written 5 years ago.
- The schema of the data written 5 ms ago and 5 years ago may also be different because of application evolvability.
- When we deploy a new version of the code then the old version can be replaced with the new version in few minutes but the data still remains the same. 
- We can migrate the old datas' encoding format into new but this takes time for a large amount of dataset which would make the current database replica unavailable from any kind of workload.
- To maintain backward compatibility(new code can read data written by old code) we can add fields with null default value such that when the old data are read then the new fields are appended with null value for that field.
- This allows the database to appear as if it was encoded with a single schema which is not the case single a database contain both newer version of data as well as historical data.


### Via services such as rest and rpc

### Distributed actor framework 


