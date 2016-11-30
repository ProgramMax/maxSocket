// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
		CurrentLinuxEndPoint = CurrentLinuxEndPoint->ai_next;
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
		return CurrentLinuxEndPoint == rhs.CurrentLinuxEndPoint;
	}

	bool AddressesIterator::operator !=( const AddressesIterator & rhs ) const
	{
		return CurrentLinuxEndPoint != rhs.CurrentLinuxEndPoint;
	}

	maxSocket::v0::IP::Address AddressesIterator::operator *() const
	{
		switch( CurrentLinuxEndPoint->ai_family )
		{
		case AF_INET:
			return maxSocket::v0::IP::Address( maxSocket::v0::IP::AddressVersion4( * reinterpret_cast< sockaddr_in * >( CurrentLinuxEndPoint->ai_addr ) ) );
		case AF_INET6:
			return maxSocket::v0::IP::Address( maxSocket::v0::IP::AddressVersion6( * reinterpret_cast< sockaddr_in6 * >( CurrentLinuxEndPoint->ai_addr ) ) );
		default:
			// We encountered an unknown address family.
			throw;
		}
	}

	AddressesIterator::AddressesIterator( addrinfo * const CurrentLinuxEndPoint )
		: CurrentLinuxEndPoint( CurrentLinuxEndPoint )
	{
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
