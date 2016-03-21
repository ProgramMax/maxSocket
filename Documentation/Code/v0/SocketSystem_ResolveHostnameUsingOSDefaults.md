# SocketSystem::ResolveHostnameUsingOSDefaults

API version: [**v0**](../v0.md)

## What is it?

This method will resolve a hostname using the OS's default DNS settings and methods.

It will map a hostname such as "google.com" to a list of IP addresses which the developer can then connect to.

This is a method of [SocketSystem](SocketSystem.md).

## Note

The OS typically blocks while resolving a hostname. This method will block as well. It is the developer's responsibility to call this on an appropriate thread.

## Signature

```c++
ResolveHostnameResults::Enum SocketSystem::ResolveHostnameUsingOSDefaults(

    const char * const         Hostname,
    const AddressFamily::Enum  AddresFamilyFilter,
    IP::Addresses &            EndPoints

) MAX_DOES_NOT_THROW;
```

## Parameters

* **Hostname**
    * Contains an ANSI null-terminated string specifying the hostname to be resolved.
	* This could be a domain like "google.com" or a subdomain like "www.google.com"
* **AddresFamilyFilter**
    * Specifies which address family results should be stored inside EndPoints upon success:

| value | Description |
| --- | --- |
| AddressFamily::IPv4 | will only populate DNS A records (IP version 4). |
| AddressFamily::IPv6 | will only populate DNS AAAA records (IP version 6). |
| AddressFamily::Any | will populate DNS A and AAAA records (IP versions 4 and 6). |

* **EndPoints**
    * On success, this pseudo-container will be able to iterate over the end points found while resolving the hostname.
	* If this parameter previously referenced another set of end points, that pseudo-container will be destroyed.

## Returns

* On success, returns **ResolveHostnameResults::Success**
* On error, returns:

| Value | Description |
| --- | --- |
| **ResolveHostnameResults::NameServerReturnedATemporaryFailure** | when the DNS server returned a temporary failure. A developer can try again later. |
| **ResolveHostnameResults::NameServerReturnedAPermanentFailure** | when the DNS server returned a permanent error. |
| **ResolveHostnameResults::OutOfMemory** | when there is not enough memory left to complete the operation. |
| **ResolveHostnameResults::NetworkHostExistsButHasNoEndPoints** | when the hostname resolves but there are no records matching the specified address family filter. |
| **ResolveHostnameResults::UnknownHostname** | when the provided hostname does not resolve. |
| **ResolveHostnameResults::SystemError** | when an error occurred from which we cannot recover. |
| **ResolveHostnameResults::LibraryError** | when there is an error in maxSocket's logic. Please notify us if you ever see a LibraryError. |
| **ResolveHostnameResults::UnknownError** | when there is an error maxSocket is not aware of. Please notify us if you ever see an UnknownError. |

## Example

```c++
// This is a pseudo-container which will "store" the results of the DNS resolution.
// It isn't actually storing anything.
// But you can iterate over it as if it were a container.
auto EndPoints = maxSocket::v0::IP::Addresses{};


// Here we resolve the domain name "google.com".
// We do this on any address family, which means we see results for both IP version 4 and IP version 6.
// The results are "stored" inside EndPoints.
auto ResolveHostnameResult = SocketSystem->ResolveHostnameUsingOSDefaults( "google.com", maxSocket::AddressFamily::Any, EndPoints );
if( ResolveHostnameResult != maxSocket::ResolveHostnameResults::Success )
{
    // error
}


// Now we can iterate over the results and connect or view.
for( const auto & EndPoint : EndPoints )
{
    std::cout << "EndPoint: " << EndPoint.GetRepresentation() << "\n";
}

```