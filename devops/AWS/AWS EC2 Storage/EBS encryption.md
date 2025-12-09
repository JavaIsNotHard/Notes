protects data using **AES-256 encryption** and integrates with **AWS KMS**

when we apply EBS encryption, it encrypts the following:
1. encrypts the data at rest inside the volume
2. all the data between the instance and the volume are also encrypted
3. all snapshots are encrypted (we can select the option not to encrypt it)
4. volumes created from encrypted snapshots


what is AWS KMS (key management system)
the actual encryption uses a data encryption key (DEK) unique to each key
this key is also encrypted by the KMS key

the performance impact from performing encryption is negligible since the ec2 instance have dedicated hardware to perform those operation

encrypt an unencrypted volume
- create a snapshot of the unencrypted volume
- create a copy of the snapshot and enable encryption in that snapshot
- then create a new volume using the encrypted snapshot which will create a encrypted volume

we can also do the following
- create a encrypted volume from an unencrypted snapshot