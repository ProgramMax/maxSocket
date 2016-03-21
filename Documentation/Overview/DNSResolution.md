# DNS resolution

API version: [**v0**](../Code/v0.md)

## What is it?

DNS is the system which **maps a domain name to an IP address**.

Your computer cannot connect to a domain name, such as "google.com". But it can only connect to IP addresses.

DNS resolution is typically the first networking step run by the client in a client-server setup. The client must find the IP of the server it wants to connect to.


## Important coding notes

The OS's default method of DNS resolution is a blocking operation. And so maxSocket also blocks on the caling thread. It is up to the developer to call it on an appropriate thread.

## Code

More specific documentation from the code below:

* [SocketSystem::CreateSocketSystem](../Code/v0/SocketSystem_CreateSocketSystem.md)
* [SocketSystem::ResolveHostNameUsingOSDefaults](../Code/v0/SocketSystem_ResolveHostNameUsingOSDefaults.md)

```c++
#include <maxSocket/SocketSystem.hpp>
#include <iostream>
#include <memory>
#include <maxSocket/IP/Address.hpp>

int main()
{
	// First, create the SocketSystem
	auto SocketSystem = std::unique_ptr< maxSocket::SocketSystem >{};
	auto CreateSocketSystemResult = maxSocket::SocketSystem::CreateSocketSystem( SocketSystem );
	if( CreateSocketSystemResult != maxSocket::CreateSocketSystemResults::Success )
	{
		return -1;
	}


	// This is a pseudo-container which will "store" the results of the DNS resolution.
	// It isn't actually storing anything.
	// But you can iterate over it as if it were a container.
	auto EndPoints = maxSocket::v0::IP::Addresses{};


	// Here we resolve the domain name "google.com".
	// We do this on any address family, which means we see results for both IP version 4 and IP version 6.
	// The results are "stored" inside EndPoints.
	auto ResolveHostNameResult = SocketSystem->ResolveHostNameUsingOSDefaults( "google.com", maxSocket::AddressFamily::Any, EndPoints );
	if( ResolveHostNameResult != maxSocket::ResolveHostNameResults::Success )
	{
		return -1;
	}


	// Now we can iterate over the results and connect or view.
	for( const auto & EndPoint : EndPoints )
	{
		std::cout << "EndPoint: " << EndPoint.GetRepresentation() << "\n";
	}

	return 0;
}
```

## How it works

Your network adapter is given an IP address to connect to in order to make DNS requests. It gets this IP address either from manual input or via DHCP (from perhaps your router or your ISP).

DNS resolution requires sending a UDP datagram to the IP of the DNS server and asking the server for a list of DNS records that match a given domain name.

There are many types of DNS records. The important records for maxSocket are A and AAAA records, which correspond to IP version 4 and IP version 6 addresses, respectively.

There result of DNS resoltion can contain multiple A and AAAA records. This provides a list of servers to the client. Sometimes the client attempts to connect to the first and works its way down the list until it establishes a connection. Sometimes the client selects a server at random. It is up to the developer to use this list in the way which is most suited for their task.

## Notes

Most OSes provide a hosts file, which overrides a DNS request. If a request is made which matches an entry in the hosts file the OS's default DNS lookup will instead use the results in the hosts file.

Different DNS servers can return different results. Only one DNS server is the authoritative server. It isn't uncommon for an ISP to provide a custom DNS server which returns different results.

## Future work

Right now, the only method of DNS resolution implemented by maxSocket is to use the OS's default. This should be ideal for the vast majority of uses.

However, we would like to provide advanced functionality for those who need it.

In the future, we will add support for:
* **multihomed connections**, such as a cell phone which can make a DNS request over either the data plan or the WiFi
* **a custom DNS resolver**, which allows skipping the hosts file, making the request through a specific adapter, and using a DNS server other than the one specified for that adapter