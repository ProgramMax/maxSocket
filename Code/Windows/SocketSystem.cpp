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

#include "PrecompiledHeader.hpp"
#include <maxSocket/SocketSystem.hpp>
#ifdef NO_PRECOMPILED_HEADER
	#include <Winsock2.h>
#endif

// These includes alow us to call getaddrinfo on systems prior to Windows XP
// more info: https://support.microsoft.com/en-us/kb/955045
#include <Ws2tcpip.h>
#include <Wspiapi.h>

#include "../Common/IP/AddressVersion4.hpp"
#include "../Common/IP/AddressVersion6.hpp"
#include <maxSocket/Socket.hpp>
#include <max/Algorithms/ScopedFunctor.hpp>
#include <max/Compiling/UnreferencedValue.hpp>

namespace maxSocket
{
namespace v0
{

	CreateSocketSystemResults::Enum SocketSystem::CreateSocketSystem(
	                                                                  std::unique_ptr< SocketSystem > & CreatedSocketSystem
	                                                                ) MAX_DOES_NOT_THROW
	{
		auto RequestedVersion = MAKEWORD( 2, 2 );
		auto WinsockVersion   = WSADATA{};
		auto WSAStartupResult = WSAStartup( RequestedVersion, & WinsockVersion );
		switch( WSAStartupResult )
		{
		case 0: // success
			break;

		case WSASYSNOTREADY: // Indicates that the underlying network subsystem is not ready for network communication.
		case WSAEPROCLIM: // A limit on the number of tasks supported by the Windows Sockets implementation has been reached.
			return CreateSocketSystemResults::SystemIsNotReady;
		case WSAVERNOTSUPPORTED: // The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.
			return CreateSocketSystemResults::NoSystemSupport;
		case WSAEFAULT: // The lpWSAData parameter is not a valid pointer.
			return CreateSocketSystemResults::LibraryError;

		default:
			return CreateSocketSystemResults::UnknownError;
		}

		auto WinsockVersionMajor = LOBYTE( WinsockVersion.wVersion );
		auto WinsockVersionMinor = HIBYTE( WinsockVersion.wVersion );

		auto IsVersionAcceptable = true;
		if( IsVersionAcceptable == false )
		{
			WSACleanup();
			return CreateSocketSystemResults::NoSystemSupport;
		}


		CreatedSocketSystem.reset( new SocketSystem() );
		return CreateSocketSystemResults::Success;
	}


	SocketSystem::~SocketSystem() MAX_DOES_NOT_THROW
	{
		WSACleanup();
	}

	ResolveHostNameResults::Enum SocketSystem::ResolveHostNameUsingOSDefaults(
	                                                                           const char * const        HostName,
	                                                                           const AddressFamily::Enum AddressFamilyFilter,
	                                                                           IP::Addresses &           EndPoints
	                                                                         ) MAX_DOES_NOT_THROW
	{
		//
		// Prepare parameters for the call to getaddrinfo.
		//
		auto WindowsAddressFamilyFilter = AF_UNSPEC;
		switch( AddressFamilyFilter )
		{
		case AddressFamily::Any:
			WindowsAddressFamilyFilter = AF_UNSPEC;
			break;
		case AddressFamily::IPv4:
			WindowsAddressFamilyFilter = AF_INET;
			break;
		case AddressFamily::IPv6:
			WindowsAddressFamilyFilter = AF_INET6;
			break;
		default:
			// maxSocket was not updated to support a newly-added AddressFamily
			return ResolveHostNameResults::LibraryError;
		}

		auto WindowsSocketFilters        = addrinfo{ 0 };
		WindowsSocketFilters.ai_family   = WindowsAddressFamilyFilter;
		WindowsSocketFilters.ai_socktype = SOCK_DGRAM;
		WindowsSocketFilters.ai_protocol = IPPROTO_UDP;
		WindowsSocketFilters.ai_flags    = 0;
		WindowsSocketFilters.ai_flags    = AI_ALL;
		// On Windows, specify AI_ALL in order to see IPv6 DNS when using AF_UNSPEC.
		// This may only happen on my machine because it doesn't have IPv6.

		addrinfo * WindowsEndPoints = nullptr;


		//
		// Make the call to getaddrinfo.
		//
		auto getaddrinfoResult = getaddrinfo( HostName, NULL, & WindowsSocketFilters, & WindowsEndPoints );
		switch( getaddrinfoResult )
		{
		case 0:
			// success
			break;

		case WSATRY_AGAIN:
			return ResolveHostNameResults::NameServerReturnedATemporaryFailure;

		case WSAEINVAL:             // An invalid value was provided for the ai_flags member of the pHints parameter.
		case WSAEAFNOSUPPORT:       // The ai_family of the pHints parameter not supported.
		case WSATYPE_NOT_FOUND:     // The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter.
		case WSAESOCKTNOSUPPORT:    // The ai_socktype member of the pHints parameter is not supported.
			return ResolveHostNameResults::LibraryError;

		case WSANO_RECOVERY:        // A nonrecoverable failure in name resolution occurred.
			return ResolveHostNameResults::SystemError;
		case WSA_NOT_ENOUGH_MEMORY: // A memory allocation failure occurred.
			return ResolveHostNameResults::OutOfMemory;
		case WSAHOST_NOT_FOUND:     // The name does not resolve for the supplied parameters or the pNodeName and pServiceName parameters were not provided.
			return ResolveHostNameResults::UnknownHostName;
		case WSANO_DATA:
			return ResolveHostNameResults::NetworkHostExistsButHasNoEndPoints;
		
		default:
			return ResolveHostNameResults::UnknownError;
		}




		EndPoints = IP::Addresses( WindowsEndPoints );

		return ResolveHostNameResults::Success;
	}

	CreateSocketAndConnectResults::Enum SocketSystem::CreateSocketAndConnect(
	                                                                          const IP::Address &         EndPoint,
	                                                                          const unsigned short        Port,
	                                                                          const Protocol::Enum        Protocol,
	                                                                          std::unique_ptr< Socket > & CreatedSocket
	                                                                        ) MAX_DOES_NOT_THROW
	{
		auto AddressFamily = AF_INET;
		switch( EndPoint.m_Version )
		{
		case IP::Version::Version4:
			AddressFamily = AF_INET;
			break;
		case IP::Version::Version6:
			AddressFamily = AF_INET6;
			break;
		default:
			return CreateSocketAndConnectResults::UnknownIPVersion;
		}

		auto WindowsSocketType = SOCK_STREAM;
		auto WindowsProtocol   = IPPROTO_TCP;
		switch( Protocol )
		{
		case Protocol::TCP:
			WindowsSocketType = SOCK_STREAM;
			WindowsProtocol   = IPPROTO_TCP;
			break;
		case Protocol::UDP:
			WindowsSocketType = SOCK_DGRAM;
			WindowsProtocol   = IPPROTO_UDP;
			break;
		default:
			return CreateSocketAndConnectResults::UnknownProtocol;
		}


		auto NativeSocketHandle = WSASocket( AddressFamily, WindowsSocketType, WindowsProtocol, NULL, NULL, 0 /* WSA_FLAG_OVERLAPPED */ );
		if( NativeSocketHandle == INVALID_SOCKET )
		{
			auto ErrorCode = WSAGetLastError();
			switch( ErrorCode )
			{
			case WSANOTINITIALISED:      // A successful WSAStartup call must occur before using this function.
			case WSAEAFNOSUPPORT:        // The specified address family is not supported
			case WSAEFAULT:              // The lpProtocolInfo parameter is not in a valid part of the process address space.
			case WSAEINPROGRESS:         // A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
			case WSAEINVAL:              // This value is caused by many things. Check the docs.
			case WSAEPROTONOSUPPORT:     // The specified protocol is not supported.
			case WSAEPROTOTYPE:          // The specified protocol is the wrong type for this socket.
			case WSAESOCKTNOSUPPORT:     // The specified socket type is not supported in this address family.
				return CreateSocketAndConnectResults::LibraryError;

			case WSAENETDOWN:            // The network subsystem has failed.
			case WSAEINVALIDPROVIDER:    // The service provider returned a version other than 2.2.
			case WSAEINVALIDPROCTABLE:   // The service provider returned an invalid or incomplete procedure table to the WSPStartup.
			case WSAEPROVIDERFAILEDINIT: // The service provider failed to initialize. This error is returned if a layered service provider (LSP) or namespace provider was improperly installed or the provider fails to operate correctly.
				return CreateSocketAndConnectResults::SystemError;
			
			case WSAEMFILE:              // No more socket descriptors are available.
				return CreateSocketAndConnectResults::NoMoreSocketDescriptorsAvailable;
			case WSAENOBUFS:             // No buffer space is available. The socket cannot be created.
				return CreateSocketAndConnectResults::OutOfMemory;

			default:
				return CreateSocketAndConnectResults::UnknownError;
			}
		}

		{ // Create a scope so on error we can destroy the socket
			auto CleanUpNativeSocket = max::Algorithms::MakeScopedFunctor( [ NativeSocketHandle ]() { closesocket( NativeSocketHandle ); } );
			max::Compiling::UnreferencedValue( CleanUpNativeSocket );

			auto AddressStorage = SOCKADDR_STORAGE{};
			switch( EndPoint.m_Version )
			{
			case IP::Version::Version4:
				{
					AddressStorage.ss_family = PF_INET;
					auto SocketAddress       = reinterpret_cast< sockaddr_in * >( & AddressStorage );
					SocketAddress->sin_addr  = EndPoint.AddressRepresentation.Version4Address.NativeIPVersion4Address;
					SocketAddress->sin_port  = htons( Port );
				}
				break;
			case IP::Version::Version6:
				{
					AddressStorage.ss_family = PF_INET6;
					auto SocketAddress       = reinterpret_cast< sockaddr_in6 * >( & AddressStorage );
					SocketAddress->sin6_addr = EndPoint.AddressRepresentation.Version6Address.NativeIPVersion6Address;
					SocketAddress->sin6_port = htons( Port );
				}
				break;
			default:
				return CreateSocketAndConnectResults::UnknownIPVersion;
			}

			auto WSAConnectResult = WSAConnect( NativeSocketHandle, reinterpret_cast< const sockaddr * >( & AddressStorage ), sizeof( AddressStorage ), NULL, NULL, NULL, NULL );
			if( WSAConnectResult == SOCKET_ERROR )
			{
				auto ErrorCode = WSAGetLastError();
				switch( ErrorCode )
				{
				case WSAEWOULDBLOCK:
					// Not an error.
					// This just means the socket is async and we don't know if it connected yet.
					break;

				case WSAECONNREFUSED:    // unable to connect
					return CreateSocketAndConnectResults::ConnectionRefused;
				case WSAETIMEDOUT:       // timed out
					return CreateSocketAndConnectResults::TimedOut;
				case WSAENETUNREACH:
					return CreateSocketAndConnectResults::NetworkUnreachable;
				case WSAEADDRNOTAVAIL:   // remote address is not valid
					return CreateSocketAndConnectResults::RemoteAddressInvalid;
				case WSAEAFNOSUPPORT:    // address in specified family cannot be used
										 // (perhaps using an IPv6 address for an IPv4 family
					return CreateSocketAndConnectResults::LibraryError;
				case WSAEHOSTUNREACH:    // unreachable host
					return CreateSocketAndConnectResults::EndPointUnreachable;
				case WSAENETDOWN:
					return CreateSocketAndConnectResults::NetworkDown;

				case WSAEALREADY:
				case WSAEINTR:           // blocking call was cancelled
				case WSAEINPROGRESS:     // we haven't made any other blocking calls on this socket, so ...
				case WSAEFAULT:          // memory of name or namelen param is not valid
				case WSAEINVAL:          // invalid parameter
				case WSAEISCONN:         // socket is already connected
				case WSAENOBUFS:         // no buffer space available
				case WSAENOTSOCK:        // descriptor is not a socket
				case WSAEOPNOTSUPP:      // the QOS params aren't valid
				case WSAEPROTONOSUPPORT: // protocol doesn't support send-on-connect
				case WSAEACCES:          // a datagram tries to broadcast
				case WSANOTINITIALISED:
				case WSAEADDRINUSE:
					return CreateSocketAndConnectResults::LibraryError;

				default:
					return CreateSocketAndConnectResults::UnknownError;
				}
			}

			// Because we have a scoped cleanup of the NativeSocketHandle,
			// create a duplicate to increment the ref count.
			auto CurrentProcessID = GetCurrentProcessId();
			auto ProtocolInfo = WSAPROTOCOL_INFO{};
			auto WSADuplicateSocketResult = WSADuplicateSocket( NativeSocketHandle, CurrentProcessID, & ProtocolInfo );
			if( WSADuplicateSocketResult == SOCKET_ERROR )
			{
				auto ErrorCode = WSAGetLastError();
				switch( ErrorCode )
				{
				case WSANOTINITIALISED: // A successful WSAStartup call must occur before using this function.
				case WSAEINVAL:         // Indicates that one of the specified parameters was invalid.
				case WSAEINPROGRESS:    // A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
				case WSAENOTSOCK:       // The descriptor is not a socket.
				case WSAEFAULT:         // The lpProtocolInfo parameter is not a valid part of the user address space.
					return CreateSocketAndConnectResults::LibraryError;

				case WSAENETDOWN:       // The network subsystem has failed.
					return CreateSocketAndConnectResults::SystemError;

				case WSAEMFILE:         // No more socket descriptors are available.
					return CreateSocketAndConnectResults::NoMoreSocketDescriptorsAvailable;

				case WSAENOBUFS:        // No buffer space is available. The socket cannot be created.
					return CreateSocketAndConnectResults::OutOfMemory;

				default:
					return CreateSocketAndConnectResults::UnknownError;
				}
			}

			CreatedSocket.reset( new Socket( NativeSocketHandle ) );
		}

		return CreateSocketAndConnectResults::Success;
	}

} // namespace v0
} // namespace maxSocket
