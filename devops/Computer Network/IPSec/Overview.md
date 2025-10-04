it works at layer 3 (network layer), it protects all traffic passing through it 

### what IPSec provides
- confidentiality  (encryption) -> data being sent cannot be read by unauthorized user
- data integrity
- authentication
- anti-replay protection -> retransmitting packets by capture legitimate packets sent by authorized users, extract security keys and new packet with those keys

### Core components
- authentication header -> provides integrity and authentication
- Encapsulating security payload -> provides confidentiality and optionally provide integrity as well as authentication
- internet key exchange -> before secure communication, parties must agree on secret keys and algorithms to be used

### Modes of operation
- transport mode -> only the payload the packet is encrypted or authenticated, the original header remain intact. **Analogy:** You put your message in a locked box (the encrypted payload) but leave the original "To" and "From" address label on the outside of the box. The route is public, but the content is private.
- tunnel mode -> the entire original IP packet is encrypted or authenticated which is then encapsulated into new IP packet with new header. used to implement VPNs by creating a secure tunnel between the two parties. **Analogy:** You take your entire, fully addressed envelope, and put it inside a larger, armored, unmarked box with a new address label on it (e.g., from your office gateway to the headquarters gateway). No one can see who the original sender and recipient are, let alone the content