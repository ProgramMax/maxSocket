// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include "gethostbyname.hpp"
#ifdef NO_PRECOMPILED_HEADER
	#include <ws2tcpip.h>
#endif
#include "../../Code/Common/IP/AddressVersion4.hpp"
#include "WindowsAddressVersion4Policy.hpp"

namespace maxSocket
{

	gethostbyname::~gethostbyname() MAX_DOES_NOT_THROW
	{
	}

	ResolveHostNameResults::Enum gethostbyname::ResolveHostName( char const * const HostName,
	                                                             AddressFamily::Enum const AddressFamilyFilter,
	                                                             std::vector< std::unique_ptr< v0::IP::Address > > & EndPoints,
	                                                             const int MaximumEndPointSanityCheck
	                                                           ) MAX_DOES_NOT_THROW
	{
		//
		// Make the call to getaddrinfo.
		//
		auto HostEntry = ::gethostbyname( HostName );
		if( HostEntry == NULL )
		{
			auto ErrorCode = WSAGetLastError();
			switch( ErrorCode )
			{
			case WSANOTINITIALISED: // A successful WSAStartup call must occur before using this function.
			case WSAEINPROGRESS:    // A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
			case WSAEINTR:          // A blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall.
				return ResolveHostNameResults::LibraryError;

			case WSAENETDOWN:       // The network subsystem has failed.	
			case WSANO_RECOVERY:    // A nonrecoverable error occurred.
				return ResolveHostNameResults::SystemError;

			case WSAHOST_NOT_FOUND: // Authoritative answer host not found.
				return ResolveHostNameResults::AuthoritiveAnswerHostNotFound;
			case WSAEFAULT:         // The name parameter is not a valid part of the user address space.
				return ResolveHostNameResults::UnknownHostName;
			case WSATRY_AGAIN:      // Nonauthoritative host not found, or server failure.
				return ResolveHostNameResults::NameServerReturnedATemporaryFailure;
			case WSANO_DATA:        // Valid name, no data record of requested type.
				return ResolveHostNameResults::NetworkHostExistsButHasNoEndPoints;

			default:
				return ResolveHostNameResults::UnknownError;
			}
		}
		

		//
		// Make the call to getaddrinfo.
		//
		std::vector< std::unique_ptr< v0::IP::Address > > TemporaryEndPoints;


		for( auto Index = int{ 0 }; HostEntry->h_addr_list[ Index ] != NULL; Index++ )
		{
			if( Index == MaximumEndPointSanityCheck )
			{
				return ResolveHostNameResults::ExceededMaximumEndPointSanityCheck;
			}

			if( HostEntry->h_addrtype == AF_INET )
			{
				TemporaryEndPoints.emplace_back( std::make_unique< maxSocket::IP::AddressVersion4 >(maxSocket::IP::WindowsAddressVersion4Policy( * reinterpret_cast< in_addr * >( HostEntry->h_addr_list[ Index ] ) ) ) );
			} else {
				// We encountered an unknown address family.
				return ResolveHostNameResults::EncounteredAnUnknownAddressFamily;
			}
		}

		std::swap( EndPoints, TemporaryEndPoints );
	
		return ResolveHostNameResults::Success;
	}

} // namespace maxSocket
