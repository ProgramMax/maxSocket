// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include <maxSocket/IP/Addresses.hpp>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	Addresses::Addresses() MAX_DOES_NOT_THROW
		: LinuxEndPoints( NULL )
	{
	}

	Addresses::Addresses( Addresses && rhs ) MAX_DOES_NOT_THROW
		: LinuxEndPoints( rhs.LinuxEndPoints )
	{
		rhs.LinuxEndPoints = NULL;
	}

	Addresses::Addresses( addrinfo * LinuxEndPoints ) MAX_DOES_NOT_THROW
		: LinuxEndPoints( LinuxEndPoints )
	{
	}

	Addresses::~Addresses() MAX_DOES_NOT_THROW
	{
		if( LinuxEndPoints != NULL )
		{
			freeaddrinfo( LinuxEndPoints );
		}
	}

	Addresses & Addresses::operator =( Addresses && rhs ) MAX_DOES_NOT_THROW
	{
		LinuxEndPoints = rhs.LinuxEndPoints;
		rhs.LinuxEndPoints = NULL;
		return *this;
	}

	AddressesIterator Addresses::begin() const MAX_DOES_NOT_THROW
	{
		return AddressesIterator( LinuxEndPoints );
	}

	AddressesIterator Addresses::end() const MAX_DOES_NOT_THROW
	{
		return AddressesIterator( NULL );
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
