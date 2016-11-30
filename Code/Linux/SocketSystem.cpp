// Copyright 2015, Chris Blume
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Chris Blume nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <maxSocket/SocketSystem.hpp>
#ifdef NO_PRECOMPILED_HEADER
	#include <max/Compiling/ThrowSpecification.hpp>
#endif

#include <maxSocket/Socket.hpp>
#include <maxSocket/AddressFamily.hpp>
#include <vector>
#include <memory>
#include <maxSocket/IP/Address.hpp>
#include "../Common/IP/AddressVersion4.hpp"
#include "../Common/IP/AddressVersion6.hpp"
#include <cstring>
#include <max/Algorithms/ScopedFunctor.hpp>
#include <max/Compiling/UnreferencedValue.hpp>
#include <unistd.h>

namespace maxSocket
{
namespace v0
{

	CreateSocketSystemResults::Enum SocketSystem::CreateSocketSystem(
	                                                                  std::unique_ptr< SocketSystem > & CreatedSocketSystem
	                                                                ) MAX_DOES_NOT_THROW
	{
		CreatedSocketSystem.reset( new SocketSystem() );
		return CreateSocketSystemResults::Success;
	}

	SocketSystem::~SocketSystem() MAX_DOES_NOT_THROW
	{
	}

	ResolveHostnameResults::Enum SocketSystem::ResolveHostnameUsingOSDefaults(
	                                                                           const char * const        Hostname,
	                                                                           const AddressFamily::Enum AddressFamilyFilter,
	                                                                           IP::Addresses &           EndPoints
	                                                                         ) MAX_DOES_NOT_THROW
	{
		//
		// Prepare parameters for the call to getaddrinfo.
		//
		auto LinuxAddressFamilyFilter = AF_UNSPEC;
		switch( AddressFamilyFilter )
		{
		case AddressFamily::Any:
			LinuxAddressFamilyFilter = AF_UNSPEC;
			break;
		case AddressFamily::IPv4:
			LinuxAddressFamilyFilter = AF_INET;
			break;
		case AddressFamily::IPv6:
			LinuxAddressFamilyFilter = AF_INET6;
			break;
		default:
			// maxSocket was not updated to support a newly-added AddressFamily
			return ResolveHostnameResults::LibraryError;
		}

		auto LinuxSocketFilters        = addrinfo{ 0 };
		LinuxSocketFilters.ai_family   = LinuxAddressFamilyFilter;
		LinuxSocketFilters.ai_socktype = SOCK_DGRAM;
		LinuxSocketFilters.ai_protocol = IPPROTO_UDP;
		LinuxSocketFilters.ai_flags    = 0;

		addrinfo * LinuxEndPoints = nullptr;


		//
		// Make the call to getaddrinfo.
		//
		auto getaddrinfoResult = getaddrinfo( Hostname, NULL, & LinuxSocketFilters, & LinuxEndPoints );
		switch( getaddrinfoResult )
		{
		case 0: // Success
			break;

		case EAI_ADDRFAMILY: // The specified network host does not have any network addresses in the requested address family.
		case EAI_BADFLAGS:   // hinst.ai_flags contains invalid flags; or, hints.ai_flags included AI_CANONNAME and name was NULL.
		case EAI_FAMILY:     // The requested address family is not supported.
		case EAI_SOCKTYPE:   // The requested socket type is not supported. This could occur, for example, if hints.ai_socktype and hints.ai_protocol are inconsistent (e.g., SOCKDGRAM and IPPROTO_TCP, respectively).
		case EAI_SERVICE:    // The requested service is not available for the requested socket type. It may be available through another socket type. For example, this error could occur if service was "shell" (a service only available on stream sockets), and either hints.ai_protocol was IPPROTO_UDP, or hints.ai_socktype was SOCK_DGRAM; or the error could occur if service was not NULL, and hints.ai_socktype was SOCK_RAW (a socket type that does not support the concept of services).
			return ResolveHostnameResults::LibraryError;

		case EAI_AGAIN:      // The name server returned a temporary failure indication. Try again later.
			return ResolveHostnameResults::NameServerReturnedATemporaryFailure;
		case EAI_FAIL:       // The name server returned a permanent failure indication.
			return ResolveHostnameResults::NameServerReturnedAPermanentFailure;
		case EAI_MEMORY:     // Out of memory.
			return ResolveHostnameResults::OutOfMemory;
		case EAI_NODATA:     // The specified network host exists, but does not have any network addresses defined.
			return ResolveHostnameResults::NetworkHostExistsButHasNoEndPoints;
		case EAI_NONAME:     // The node or service is not known; or both node and service are NULL; or AI_NUMERICSERV was specified in hints.ai_flags and service was not a numeric port-number string.
			return ResolveHostnameResults::UnknownHostname;
		case EAI_SYSTEM:     // Other system error, check errno for details.
			return ResolveHostnameResults::SystemError;

		default:
			return ResolveHostnameResults::UnknownError;
		}




		EndPoints = IP::Addresses( LinuxEndPoints );

		return ResolveHostnameResults::Success;
	}

	CreateSocketAndConnectResults::Enum SocketSystem::CreateSocketAndConnect(
	                                                                          const IP::Address &         EndPoint,
	                                                                          const unsigned short        Port,
	                                                                          const Protocol::Enum        Protocol,
	                                                                          std::unique_ptr< Socket > & CreatedSocket
	                                                                        ) MAX_DOES_NOT_THROW
	{
		auto AddressFamily = PF_INET;
		switch( EndPoint.m_Version )
		{
		case IP::Version::Version4:
			AddressFamily = PF_INET;
			break;
		case IP::Version::Version6:
			AddressFamily = PF_INET6;
			break;
		default:
			return CreateSocketAndConnectResults::LibraryError;
		}

		auto LinuxSocketType = SOCK_STREAM;
		auto LinuxProtocol   = IPPROTO_TCP;
		switch( Protocol )
		{
		case Protocol::TCP:
			LinuxSocketType = SOCK_STREAM;
			LinuxProtocol   = IPPROTO_TCP;
			break;
		case Protocol::UDP:
			LinuxSocketType = SOCK_DGRAM;
			LinuxProtocol   = IPPROTO_UDP;
			break;
		default:
			return CreateSocketAndConnectResults::LibraryError;
		}


		auto NativeSocketHandle = socket( AddressFamily, LinuxSocketType, LinuxProtocol );
		if( NativeSocketHandle == -1 )
		{
			auto ErrorCode = errno;
			switch( ErrorCode )
			{
			case EAFNOSUPPORT:    // The implementation does not support the specified address family.
			case EPROTONOSUPPORT: // The protocol is not supported by the address family, or the protocol is not supported by the implementation.
			case EPROTOTYPE:      // The socket type is not supported by the protocol.
				return CreateSocketAndConnectResults::SystemError;
			case EMFILE:          // No more file descriptors available for this process.
			case ENFILE:          // No more file descriptors available for the system.
				return CreateSocketAndConnectResults::NoMoreSocketDescriptorsAvailable;
			case EACCES:          // The process does not have the appropriate privileges.
				return CreateSocketAndConnectResults::NotAuthorized;
			case ENOBUFS:         // Insufficient resources were available in the system to perform the operation.
			case ENOMEM:          // Insufficient memory was available to fulfill the request.
				return CreateSocketAndConnectResults::OutOfMemory;
			default:
				return CreateSocketAndConnectResults::UnknownError;
			}
		}

		{ // Create a scope so on error we can destroy the socket
			auto CleanUpNativeSocket = max::Algorithms::MakeScopedFunctor( [SocketHandle=NativeSocketHandle]() { close( SocketHandle ); } );
			max::Compiling::UnreferencedValue( CleanUpNativeSocket );

			sockaddr * Address = nullptr;
			auto AddressLength = size_t{ 0 };
			switch( EndPoint.m_Version )
			{
			case IP::Version::Version4:
				{
					auto LinuxAddress       = EndPoint.AddressRepresentation.Version4Address.NativeIPVersion4Address;
 					LinuxAddress.sin_family = AF_INET;
					LinuxAddress.sin_port   = htons( Port );
					Address                 = reinterpret_cast< sockaddr * >( & LinuxAddress );
					AddressLength           = sizeof( LinuxAddress );
				}
				break;
			case IP::Version::Version6:
				{
					auto LinuxAddress        = EndPoint.AddressRepresentation.Version6Address.NativeIPVersion6Address;
					LinuxAddress.sin6_family = AF_INET6;
					LinuxAddress.sin6_port   = Port;
					Address                  = reinterpret_cast< sockaddr * >( & LinuxAddress );
					AddressLength            = sizeof( LinuxAddress );
				}
				break;
			default:
				return CreateSocketAndConnectResults::LibraryError;
			}
			auto connectResult = connect( NativeSocketHandle, reinterpret_cast< sockaddr * >( Address ), AddressLength );
			if( connectResult == -1 )
			{
				auto ErrorCode = errno;
				switch( ErrorCode )
				{
				case EADDRNOTAVAIL: // The specified address is not available from the local machine.
				case EAFNOSUPPORT:  // The specified address is not a valid address for the address family of the specified socket.
				case EALREADY:      // A connection request is already in progress for the specified socket.
				case EBADF:         // The socket argument is not a valid file descriptor.
				case EINPROGRESS:   // O_NONBLOCK is set for the file descriptor for the socket and the connection cannot be immediately established; the connection shall be established asynchronously.
				case EISCONN:       // The specified socket is connection-mode and is already connected.
				case ENOTSOCK:      // The socket argument does not refer to a socket.
				case EPROTOTYPE:    // The specified address has a different type than the socket bound to the specified peer address.
				case EINVAL:        // The address_len argument is not a valid length for the address family; or invalid address family in the sockaddr structure.
				case ENAMETOOLONG:  // A component of a pathname exceeded {NAME_MAX} characters, or an entire pathname exceeded {PATH_MAX} characters.
									// This error can also match this case:
									// Pathname resolution of a symbolic link produced an intermediate result whose length exceeds {PATH_MAX}.
				case ENOENT:        // A component of the pathname does not name an existing file or the pathname is an empty string.
				case ENOTDIR:       // A component of the path prefix of the pathname in address is not a directory.
				case EACCES:        // Search permission is deined for a component of the path prefix; or write access to the named socket is denied.
				case EADDRINUSE:    // Attempt to establish a connection that uses addresses that are already in use.
				case ELOOP:         // More than {SYMLOOP_MAX} symbolic links were encountered during resolution of the pathname in address.
									// This error can also match this case:
									// A loop exists in symbolic links encountered during resolution of the pathname in address.
				case EOPNOTSUPP:    // The socket is listening and cannot be connected.
					return CreateSocketAndConnectResults::LibraryError;
				case ECONNREFUSED:  // The target address was not listening for connections or refused the connection request.
					return CreateSocketAndConnectResults::ConnectionRefused;
				case ENETUNREACH:   // No route to the network is present.
					return CreateSocketAndConnectResults::NetworkUnreachable;
				case ETIMEDOUT:     // The attempt to connect timed out before a connection was made.
					return CreateSocketAndConnectResults::TimedOut;
				case EIO:           // An I/O error occurred whil reading from or writing to the file system.
					return CreateSocketAndConnectResults::SystemError;
				case ECONNRESET:    // Remote host reset the connection request.
					return CreateSocketAndConnectResults::ConnectionResetByEndPoint;
				case EHOSTUNREACH:  // The destination host cannot be reached (probably because the host is down or a remote router cannot reach it).
					return CreateSocketAndConnectResults::EndPointUnreachable;
				case ENETDOWN:      // The local network interface used to reach the destinatino is down.
					return CreateSocketAndConnectResults::NetworkDown;
				case ENOBUFS:       // No buffer space is available.
					return CreateSocketAndConnectResults::OutOfMemory;
				case EINTR:         // The attempt to establish a connection was interrupted by delivery of a signal that was caught; the connection shall be established asynchronously.
					return CreateSocketAndConnectResults::Interrupted;
				default:
					return CreateSocketAndConnectResults::UnknownError;
				}
			}

			// Because we have a scoped cleanup of the NativeSocketHandle,
			// create a duplicate to increment the ref count.
			auto DuplicatedSocketHandle = dup( NativeSocketHandle );
			if( DuplicatedSocketHandle == -1 )
			{
				auto ErrorCode = errno;
				switch( ErrorCode )
				{
				case EBADF:  // oldfd isn't an open file descriptor, or newfd is out of the allowed range for file descriptors.
				case EBUSY:  // (Linux only) This may be returned by dup2() or dup3() during a race condition with open(2) and dup().
				case EINTR:  // The dup2() or dup3() call was interrupted by a signal; see signal(7).
				case EINVAL: // (dup3()) flags contains an invalid value. Or, oldfd was equal to newfd.
					return CreateSocketAndConnectResults::LibraryError;

				case EMFILE: // The process already has the maximum number of file descriptors open and tried to open a new one.
					return CreateSocketAndConnectResults::NoMoreSocketDescriptorsAvailable;

				default:
					return CreateSocketAndConnectResults::UnknownError;
				}
			}

			CreatedSocket.reset( new Socket( DuplicatedSocketHandle ) );
		}

		return CreateSocketAndConnectResults::Success;
	}

} // namespace v0
} // namespace maxSocket
