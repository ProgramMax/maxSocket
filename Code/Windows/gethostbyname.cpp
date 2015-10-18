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
	                                                             std::vector< std::unique_ptr< IP::Address > > & EndPoints,
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
		std::vector< std::unique_ptr< IP::Address > > TemporaryEndPoints;


		for( auto Index = int{ 0 }; HostEntry->h_addr_list[ Index ] != NULL; Index++ )
		{
			if( Index == MaximumEndPointSanityCheck )
			{
				return ResolveHostNameResults::ExceededMaximumEndPointSanityCheck;
			}

			if( HostEntry->h_addrtype == AF_INET )
			{
				TemporaryEndPoints.emplace_back( std::make_unique< IP::AddressVersion4 >( IP::WindowsAddressVersion4Policy( * reinterpret_cast< in_addr * >( HostEntry->h_addr_list[ Index ] ) ) ) );
			} else {
				// We encountered an unknown address family.
				return ResolveHostNameResults::EncounteredAnUnknownAddressFamily;
			}
		}

		std::swap( EndPoints, TemporaryEndPoints );
	
		return ResolveHostNameResults::Success;
	}

} // namespace maxSocket