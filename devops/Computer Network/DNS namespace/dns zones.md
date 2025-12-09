set of dns records for a domain or a subdomain maintained by a authoritative dns server
basically a branch in the dns hierarchy

this is a portion of the DNS namespace owned and managed by a single organization
the DNS namespace here refers to the global DNS where the global DNS is composed of many DNS zones 

each individual organization will have their own DNS zone registered such as google.com or amazon.com and many more. these google and amazon fall under the same DNS zone

dns zone exists at multiple levels including the root level as well as TLD level as well as the authoritative level
the DNS contains a special record at the start of each zone called the start of authority (SOA) record. this record signifies the start of the zone and contains some important metadata about the zone. this means that each level in the DNS hierarchy will have its own [[SOA record]] associated with itself

## Delegation

delegation in process where the parent zone hands over responsibility for a subdomain to another authoritative DNS server

the root server replies with a delegation (which is a list of server responsible for the server below itself)