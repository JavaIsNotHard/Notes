- symmetric key system (the key for encryption and decryption are private)
- public key system (the key for encryption and decryption is public)

old cryptographic techniques:
- monoalphabetic ciphers (single cipher text row)
	- each letter is mapped to another letter which forms the cipher text 
- polyalphabetic ciphers (n cipher text row)

modern cryptographic techniques:
 - stream ciphers (used in wireless LANS)
 - block ciphers (used in PGN, SSL, IPsec and more)

Block Ciphers 
divide the plaintext message into n blocks which has m equal number of bits in each block. 
Each block of m bits is then one to one mapped to another m bit value.
Disadvantage:
1. Storing the cipher table for each mapping is costly since suppose a 64 bit cipher block would produce a value large to store or transmit over the network 
Another technique is to divide the block into manageable number of bits for example 8 such that the message is divided into n blocks of 8 bits each. Each block will then have a transformation function which does the same mapping and produces a 8 bit output. The result of all the 8 bits are then scrambled and then placed for another round of the same method.
Disadvantage:
1. two blocks in different message can be the same bits representing a common ASCII value. This would mean that an attacker could potentially guess the clear text when it sees identical cipher text blocks. 

Addition to the message block and the cipher block, we could also use a random block of the same bit length to introduce randomness in the cipher text. 

let m(i) represent a message block and r(i) represent a random block then we could compute the cipher block using the formula c(i) = Ks(m(i) xor r(i)). Then the sender could send the cipher block c(i) along with the random block r(i) to decrypt the message.

Cipher block chaining:
- A random k-bit string called a Initialization Vector (IV) is send in plain text. 
- This IV is used as follows c(1) = Ks(m(1) xor IV). The obtained cipher block is then used in another iteration for another cipher block as follows c(2) = Ks(m(2) xor c(1)).
What problem does this method solve?
- For each message block, previous we had to send an additional random block. This overhead of sending additional blocks is removed. 

Public key cryptography 
public key and private key 
public key is known to all the hosts 
private key is only known to the host themselves
an encryption algorithm (SHA-1 or MD5) is used to encrypt any plain text into a cipher text which use either the public key or the private key. Both the public key and the private key can be used to encrypt and decrypt messages. 
RSA algorithm named after its creators 
