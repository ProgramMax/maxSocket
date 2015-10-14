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
#include "getaddrinfo.hpp"
#ifdef NO_PRECOMPILED_HEADER
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <ws2tcpip.h>
#endif
#include "../../Code/Common/IP/AddressVersion4.hpp"
#include "../../Code/Common/IP/AddressVersion6.hpp"
#include <max/Algorithms/ScopedFunctor.hpp>
#include <max/Compiling/UnreferencedValue.hpp>
#include "WindowsAddressVersion4Policy.hpp"
#include "WindowsAddressVersion6Policy.hpp"

namespace maxSocket
{

	getaddrinfo::getaddrinfo( const getaddrinfoFunctionPointers & FunctionPointers ) MAX_DOES_NOT_THROW
		: FunctionPointers( FunctionPointers )
	{
	}

	getaddrinfo::~getaddrinfo() MAX_DOES_NOT_THROW
	{
	}

	ResolveHostNameResults::Enum getaddrinfo::ResolveHostName( char const * const HostName,
	                                                           AddressFamily::Enum const AddressFamilyFilter,
	                                                           std::vector< std::unique_ptr< IP::Address > > & EndPoints,
	                                                           const int MaximumEndPointSanityCheck
	                                                         ) MAX_DOES_NOT_THROW
	{
		//
		// Prepare parameters for the call to getaddrinfo.
		//
		auto WindowsAddressFamilyFilter = AF_UNSPEC;
		switch( AddressFamilyFilter )
		{
		case AddressFamily::IPv4:
			WindowsAddressFamilyFilter = AF_INET;
			break;
		case AddressFamily::IPv6:
			WindowsAddressFamilyFilter = AF_INET6;
			break;
		default:
			break;
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
		auto getaddrinfoResult = FunctionPointers.getaddrinfo( HostName, NULL, & WindowsSocketFilters, & WindowsEndPoints );
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


		//
		// Parse the results of the call to getaddrinfo.
		//
		{
			auto CleanupWindowsEndPointList = max::Algorithms::MakeScopedFunctor( [FunctionPointers=this->FunctionPointers, WindowsEndPoints]() { FunctionPointers.freeaddrinfo( WindowsEndPoints ); } );
			max::Compiling::UnreferencedValue( CleanupWindowsEndPointList );

			std::vector< std::unique_ptr< IP::Address > > TemporaryEndPoints;

		
			auto RemainingEndPointsForSanityCheck = int{ MaximumEndPointSanityCheck };
			for( auto CurrentWindowsEndPoint = WindowsEndPoints; CurrentWindowsEndPoint != NULL; CurrentWindowsEndPoint = CurrentWindowsEndPoint->ai_next )
			{
				if( RemainingEndPointsForSanityCheck-- == 0 )
				{
					return ResolveHostNameResults::ExceededMaximumEndPointSanityCheck;
				}

				switch( CurrentWindowsEndPoint->ai_family )
				{
				case AF_INET:
					TemporaryEndPoints.emplace_back( std::make_unique< IP::AddressVersion4 >( IP::WindowsAddressVersion4Policy( reinterpret_cast< sockaddr_in * >( CurrentWindowsEndPoint->ai_addr )->sin_addr ) ) );
					break;
				case AF_INET6:
					TemporaryEndPoints.emplace_back( std::make_unique< IP::AddressVersion6 >( IP::WindowsAddressVersion6Policy( reinterpret_cast< sockaddr_in6 * >( CurrentWindowsEndPoint->ai_addr )->sin6_addr ) ) );
					break;
				default:
					// We encountered an unknown address family.
					return ResolveHostNameResults::EncounteredAnUnknownAddressFamily;
				}
			}

			std::swap( EndPoints, TemporaryEndPoints );
	
			return ResolveHostNameResults::Success;
		}
	}

} // namespace maxSocket
