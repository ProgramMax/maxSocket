# SocketSystem

API version: [**v0**](../v0.md)

## What is it?

The SocketSystem class is the starting point for all of maxSocket.

A developer starts using maxSocket by calling [CreateSocketSystem](SocketSystem_CreateSocketSystem.md).

From there, a developer may choose to resolve a host name via [ResolveHostNameUsingOSDefaults](SocketSystem_ResolveHostNameUsingOSDefaults.md) and/or
connect to an end point via [CreateSocketAndConnect](SocketSystem_CreateSocketAndConnect.md).

## Note

Even though some methods of socket communication are considered connectionless (they do not perform a handshake nor maintain state), maxSocket uses the word "connect" to mean establish a route to the end point.

So a developer would call [CreateSocketAndConnect](SocketSystem_CreateSocketAndConnect.md) even when creating a UDP socket.

## Methods of interest

* [CreateSocketSystem](SocketSystem_CreateSocketSystem.md)
* [ResolveHostNameUsingOSDefaults](SocketSystem_ResolveHostNameUsingOSDefaults.md)
* [CreateSocketAndConnect](SocketSystem_CreateSocketAndConnect.md)

## Less interesting methods

* [~SocketSystem (destructor)](SocketSystem_dtor.md)