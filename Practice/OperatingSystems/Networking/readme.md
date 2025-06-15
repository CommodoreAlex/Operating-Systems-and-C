# Network Programming 

A **socket** is an endpoint for communication between two systems over a network. It enables data exchange between a **client** and a **server** using protocols like TCP and UDP.

## Key Concepts

### Socket Types
- **Stream (`SOCK_STREAM`)** → Reliable, connection-based (used in TCP).
- **Datagram (`SOCK_DGRAM`)** → Unreliable, connectionless (used in UDP).

### Socket Components
- **IP Address** → Identifies a device on the network.
- **Port Number** → Identifies the specific service or application.

## Basic TCP Socket Flow

1. **Server creates a socket** → `socket()`
2. **Server binds to an IP & port** → `bind()`
3. **Server listens for connections** → `listen()`
4. **Client connects to the server** → `connect()`
5. **Server accepts the client** → `accept()`
6. **Data is exchanged** → `send()` / `recv()`

Sockets are essential in networking and are widely used in web servers, messaging applications, and cybersecurity tools.

---

![image](https://github.com/user-attachments/assets/173c0c18-b1ca-4296-944c-5118c3e3ee1f)
