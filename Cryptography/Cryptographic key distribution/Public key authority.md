![[Screenshot 2024-10-19 at 17.49.07.png]]

The same dynamic distribution authority is used as before but this time the private key is only known to the authority server itself. A public key of the authority server is known to all users which  is used by the users to verify that the certificate that the authority provides is valid.

In the above figure, total of 7 request and response are sent from A to authority, B to authority and A to B. The first 5 messages are the initialization step and needs to be done only once. After that the public keys can be cached for future use by both the users.

This approach has the same drawback of leakage of the authority's private key

