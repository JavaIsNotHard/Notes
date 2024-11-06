- To provide structure to the design of network protocol, network designers organize protocols and the network hardware and software that implements the protocol in layers.
- The basic idea of protocol layering is to group a bunch of protocols having similar functionality into a single layer.
- A layer provides some [[service]] that are made available to layer above it. This is called the [[service model]].
- There are potential drawbacks for using layered approach. This includes:
	- one layer may duplicate lower-level functionality.
	- functionality at one layer may need information that is present only in another layer.

The TCP/IP stack has 5 layers including:
- [[Chapter-1/1.5/Application layer]]
- [[Chapter-1/1.5/Transport layer]]
- [[Network layer]]
- [[Chapter-1/1.5/Link layer]]
- [[Physical layer]]