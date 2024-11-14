- cache memory sits in between the CPU register and the main memory
- different levels of cache memory: L1, L2 and L3. 
- L1 can access data at 4 clock cycles (register can access in 1), L2 can access in 10 clock cycles whereas L3 can access in 50 clock cycles. 

- each memory address has m bits that form M = 2^m unique addresses.
- cache is organized as an array of S = 2^m cache sets 
- each set consists of E = 2^e  cache lines 
- each line consists of B = 2^b data blocks
![[Screenshot 2024-11-14 at 09.58.08.png]]
- each line also contains bits such as valid and tag bits
- valid bit indicate whether the line contains meaningful information
- tag bit uniquely identify the block stored in the cache line.

- The size of the cache is determined as C = S * E * B

- if data is not found in the CPU registers then it first searches the cache unit. How does the cache know if it contains the data or not?
- This can be done by inspecting the bits of the address
![[Screenshot 2024-11-14 at 09.58.20.png]]
- address is divided into 3 segments, the t bits, s bits and the b bits.
- the s bit tells in which set the word must be stored in.
- the t bit tells in which line the word must be stored at.
- The line contains the data on if the valid bit in the line is set and the value of the t tag in the line and the value of t bits in the address matches.
- Once we identify the line then we can use b bits as block offset to know which block contains the data. 

