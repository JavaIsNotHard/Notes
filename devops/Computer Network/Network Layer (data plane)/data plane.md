based on the information that the [[control plane]] gives, it moves the packet from the input to the respective output interface

the data plan is responsible for forwarding

The generic router architecture looks like this
![[Pasted image 20250913180204.png]]
it contains four main components
1. [[input port]]
2. [[output port]]
3. [[routing processor]]
4. [[switching fabric]]


the input port, output port and switching fabric are implemented in hardware level because the speed at which packets arrive are very fast and each packet need to be processed very fast. these components fall under the data plane of the router. these operate in the order of nanoseconds.

the control plane can be slower than the data plane and can operate at milliseconds rather than nanoseconds because the computational overhead is greater and requires more time
