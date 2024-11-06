Components of wireless networks:
- wireless hosts 
- wireless links
- base station: responsible from sending and receiving data to and from a wireless host that is associated with that base station. What does association mean here? if the host is within the communication distance of the base station and if the host uses the base station to relay data to and from a larger network. Access points and cellular towers are examples of base station
- network infrastructure: a larger network with which the wireless host wish to communicate with


802.11 architecture 
- basic service set: contains one or more wireless stations and a central base station known as access points.
- Access point: each basic service set needs at least one access point that connects to a wired device such as routers and switches. two basic service set are connected using this router and switches.
- wireless station: one or more than one wireless station form a basic service set 

service set identifier (SSID) to a access point
channel number to the access point
Each access point operates in the range of 2.4 to 2.4835 ghz which means that within this 85 mhz band, 802.11 defines 11 partially overlapping channels. Within these 11 channels, channels 1, 6, and 11 are non-overlapping channels which means that data send to channel 1, 6, and 11 could never collide with one other. So we could assign 3 AP's within channel number 1, 6 and 11 and get 3 times the maximum transmission rate by connected those 3 APs with a single switch
A WiFi jungle is where multiple APs broadcast their singal to a wireless host or station. Within this jungle the wireless host can only connect to one AP or associate with one AP. What is association? the wireless station can only send link layer frame using this AP to the larger network. As mentioned previous the AP is connected to a switch which in turn is connected to a larger network. Each AP is also associated with a subnet. 

link-layer acknowledgement
when the destination receives a frame that passes the CRC check then it waits for a short interval of time known as short inter frame spacing. If the transmitting station does not receive an acknowledgement with a certain time interval then it retransmits, if the transmitting station does not receive an acknowledgement for any of the frames then it discards the frame 
Initially the transmitting station waits for a distributed inter-frame space time. This time is chosen randomly and a counter is started counting the value backwards until zero. Once zero the transmission starts. 
If acknowledgement is not received within a certain time period then it goes to the backoff phase where the value of DIFS is chosen from a larger interval to make the randomness more random
Why does CSMA/CA wait before transmitting a frame?
CSMA/CD can detect collision and hence avoid it as well but CSMA/CA sense the channel and transmit the frame entirely without any detection done. Suppose two stations were waiting for a third station to end their transmission and if both the station were to send at the same time the third station were to finish then it would cause collision this is why random backoff time is taken before transmitting the frame.
But due to the hidden terminal and fading problem the stations may not be able to sense the channel properly to avoid collision.
In order to avoid this problem 802.11 protocol uses a short request to send (RTS) and clear to send (CTS) control frame to reserve access to the channel. Before send a data frame, the RTS control frame is send to reserve the channel by specifying to the receiver about the time required to send the entire frame and the acknowledgement frame. The receiver then broadcasts a CTS frame to all the station for two reasons: 1 to acknowledge the sender and two to make sure that other station refer from sending for this interval of time.
Because this process is time and channel resource consuming, stations only sends RTS and CTS when the data frame is larger than a certain threshold.

802.11 frames
payload and crc field -> payload -> 2312 bytes control frame to reserve access to the channel. Before send a data frame, the RTS control frame is send to reserve the channel by specifying to the receiver about the time required to send the entire frame and the acknowledgement frame. The receiver then broadcasts a CTS frame to all the station for two reasons: 1 to acknowledge the sender and two to make sure that other station refer from sending for this interval of time.
Because this process is time consuand resource channel resource consuming, stations only sends RTS and CTS when the data frame is larger than a certain threshold.

802.11 frames
payload and crc field -> payload -> 0-2312 bytes -> CRC -> 4 bytes
address field -> 4 addresses each with 6 bytes. Why 4 addresses?
APs are connected to the internet via a switch or a router. Suppose the router wants to send packet to one of the hosts in the BSS of the AP then it first sends a ethernet frame with the host as the dst and switch or router as the src (the address is a MAC address). Once the packet reaches the AP (since AP connects the host with the switch) it converts the 802.3 frame into a 802.11 frame where address 2 is set to the src which is the AP's address, address 1 as the dst which is the hosts's address and address 3 as the switches address. If host wants to send a response to the switch then it sets the source to its own address, dst to the APs address and address 3 is filled with the switches address once the AP receives the frame then it again converts the 802.11 frame into a 802.3 frame and sends it to the switch

Mobility in the same subnet

