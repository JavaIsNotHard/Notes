It is a communication protocol between the SDN controller and all the controlled network devices and packet switches. This protocol operates over an TCP connection running at port 6653
The following are the main messages flowing from the controller to the controlled devices: 
- configuration: used to set the switch's configuration parameters
- modify-state: add/delete or modify entries in the switch's flow table
- read-state: collect statistics and counter values from the switch's flow table. 
- send-packet: forward a packet out to one of its port

The following are the main messages flowing from the SDN controlled device to the SDN controller:
- Flow-removed: informs the sdn controller about the removal of flow table entry
- port-status: information about change in port status
- packet-in: packet arriving at switch input port and not matching any flow table entry is passed to the sdn controller for further processing.