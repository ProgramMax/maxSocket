# SocketSystem::CreateSocketAndConnect

API version: [**v0**](../v0.md)

## What is it?

This method will create a socket and connect to the spefied end point.

This is a method of [SocketSystem](SocketSystem.md).

## Note

In this context, "connect" means setup a line of communication to the end point. A protocol which is said to be connectionless (does not perform a handshake nor maintain state) such as UDP will still needs to be setup.

The actual socket communication has not yet been polished. As a consequence, this function is likely to change soon.

## Signature

```c++
CreateSocketAndConnectResults::Enum SocketSystem::CreateSocketAndConnect(
    const IP::Address &         EndPoint,
    const unsigned short        Port,
    const Protocol::Enum        Protocol,
    std::unique_ptr< Socket > & CreatedSocket
) MAX_DOES_NOT_THROW;
```

## Parameters

* **EndPoint**
    * This is the end point to which a connection will be established.
* **Port**
    * This is the port at the end point to connect to.
* **Protocol**
    * Specifies which protocol to connect using:

| value | Description |
| --- | --- |
| Protocol::TCP | will perform a handshake, attempt to keep messages ordered, and notify when the end point can no longer be reached. |
| Protocol::UDP | will only touch the network when instructed to but does not know if the message was received. |

* **CreatedSocket**
    * On success, this is populated with the socket which was created and connected.
	* If this parameter previously referenced another socket, that socket will be destroyed.

## Returns

* On success, returns **CreateSocketAndConnectResults::Success**
* On error, returns:

| Value | Description |
| --- | --- |
| **CreateSocketAndConnectResults::SystemError** | when the system does not support the type of connection requested. |
| **CreateSocketAndConnectResults::NoMoreSocketDescriptorsAvailable** | when there are not enough socket descriptors left for the system fulfill the request. |
| **CreateSocketAndConnectResults::NotAuthorized** | when the process does not have permission to create the requested socket. |
| **CreateSocketAndConnectResults::OutOfMemory** | when the system does not have enough memory to fulfill the request. |
| **CreateSocketAndConnectResults::ConnectionRefused** | when the end point turned down the connection. |
| **CreateSocketAndConnectResults::TimedOut** | when the connection to the end point did not complete in time. |
| **CreateSocketAndConnectResults::NetworkUnreachable** | when the underlying network cannot be reached. |
| **CreateSocketAndConnectResults::EndPointUnreachable** | when the end point cannot be reached. |
| **CreateSocketAndConnectResults::NetworkDown** | when the underlying network has gone down. |
| **CreateSocketAndConnectResults::ConnectionResetByEndPoint** | when the underlying network has gone down. |
| **CreateSocketAndConnectResults::Interrupted** | when the connection was interrupted by a system event. |
| **CreateSocketAndConnectResults::LibraryError** | when there is an error in maxSocket's logic. Please notify us if you ever see a LibraryError. |
| **CreateSocketAndConnectResults::UnknownError** | when there is an error maxSocket is not aware of. Please notify us if you ever see an UnknownError. |