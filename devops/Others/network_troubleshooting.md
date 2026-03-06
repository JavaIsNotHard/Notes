# Network Troubleshooting Playbook (tcpdump + ss)

  

## Goal

Quickly determine **where a failure lives**: network path, kernel/socket layer, or application logic.

  

---

  

## Step 1: Is traffic reaching the host?

**Tool:** tcpdump

  

```bash

sudo tcpdump -i any tcp port 8000

```

  

### Interpret

- **No SYN packets at all**

- Problem is **outside the box**

- Check: routing, firewall rules, load balancer, security groups

- **SYN packets visible**

- Traffic is reaching the machine

- Move inward

  

---

  

## Step 2: Is anything listening?

**Tool:** ss

  

```bash

ss -tunlp

```

  

### Interpret

- **Port NOT in LISTEN**

- App not running, crashed, or bound to wrong port/IP

- Kernel cannot accept connections

- **Port IS in LISTEN**

- Kernel is ready

- Move inward again

  

---

  

## Step 3: Does the TCP handshake complete?

**Tool:** tcpdump

  

### Interpret

- **SYN → no SYN-ACK**

- Listener missing or kernel rejecting

- **SYN → SYN-ACK → ACK**

- Network + kernel are healthy

- Connection established

  

---

  

## Step 4: Does the application behave correctly?

**Tool:** curl + tcpdump

  

```bash

curl http://localhost:8000/some-path

```

  

### Interpret

- **Handshake + data packets + error response**

- Not a networking issue

- Bug lives in application logic (routes, handlers, config)

  

---

  

## Mental Model Summary

  

| Observation | Root Cause Layer |

|------------|------------------|

| No packets | Network / infra |

| SYNs only | Socket / listener |

| Handshake + errors | Application |

  

---

  

## Golden Rule

Always debug **outside → kernel → application**. Never guess.

---

  

## Protocol and Port Filtering (tcpdump)

  

Filtering is how you turn tcpdump from a firehose into a scalpel.

  

### Capture only TCP traffic

```bash

sudo tcpdump -i any tcp

```

**Use when:** debugging connection setup, handshakes, resets, retries

**What you’ll see:** SYN, SYN-ACK, ACK, FIN, RST packets — the full TCP lifecycle

  

---

  

### Capture only UDP traffic

```bash

sudo tcpdump -i any udp

```

**Use when:** debugging DNS, metrics, streaming, or anything connectionless

**What you’ll see:** standalone request/response packets with no handshake

  

---

  

### Capture traffic on a specific port

```bash

sudo tcpdump -i any tcp port 8000

```

**Use when:** you know the service port and want to ignore everything else

**What you’ll see:** only packets destined for or originating from port 8000

  

---

  

### Combine protocol + port (most common)

```bash

sudo tcpdump -i any tcp port 443

```

**Use when:** debugging a specific TCP service

**Why:** protocol filter removes noise first, port filter narrows the target

  

---

  

### Mental Model

- **Protocol filter answers:** “What *kind* of traffic is this?”

- **Port filter answers:** “Which *service* is this traffic for?”

- Start broad (protocol), then narrow (port)