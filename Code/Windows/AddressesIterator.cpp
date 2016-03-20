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
#include <maxSocket/IP/AddressesIterator.hpp>
#include <maxSocket/IP/Address.hpp>
#include <maxSocket/IP/AddressVersion4.hpp>
#include <maxSocket/IP/AddressVersion6.hpp>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	AddressesIterator & AddressesIterator::operator ++()
	{
		CurrentEndPoint = CurrentEndPoint->ai_next;
		return *this;
	}

	AddressesIterator AddressesIterator::operator ++( int )
	{
		AddressesIterator Temp( *this );
		operator++();
		return Temp;
	}

	bool AddressesIterator::operator ==( const AddressesIterator & rhs ) const
	{
		return CurrentEndPoint == rhs.CurrentEndPoint;
	}

	bool AddressesIterator::operator !=( const AddressesIterator & rhs ) const
	{
		return CurrentEndPoint != rhs.CurrentEndPoint;
	}

	maxSocket::v0::IP::Address AddressesIterator::operator *() const
	{
		switch( CurrentEndPoint->ai_family )
		{
		case AF_INET:
			return maxSocket::v0::IP::Address( maxSocket::v0::IP::AddressVersion4( reinterpret_cast< sockaddr_in * >( CurrentEndPoint->ai_addr )->sin_addr ) );
		case AF_INET6:
			return maxSocket::v0::IP::Address( maxSocket::v0::IP::AddressVersion6( reinterpret_cast< sockaddr_in6 * >( CurrentEndPoint->ai_addr )->sin6_addr ) );
		default:
			// We encountered an unknown address family.
			throw;
		}
	}

	AddressesIterator::AddressesIterator( addrinfo * const CurrentEndPoint )
		: CurrentEndPoint( CurrentEndPoint )
	{
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
