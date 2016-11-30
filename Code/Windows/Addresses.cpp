// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxSocket/IP/Addresses.hpp>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	Addresses::Addresses() MAX_DOES_NOT_THROW
		: EndPoints( NULL )
	{
	}

	Addresses::Addresses( Addresses && rhs ) MAX_DOES_NOT_THROW
		: EndPoints( rhs.EndPoints )
	{
		rhs.EndPoints = NULL;
	}

	Addresses::Addresses( addrinfo * EndPoints ) MAX_DOES_NOT_THROW
		: EndPoints( EndPoints )
	{
	}

	Addresses::~Addresses() MAX_DOES_NOT_THROW
	{
		if( EndPoints != NULL )
		{
			freeaddrinfo( EndPoints );
		}
	}

	Addresses & Addresses::operator =( Addresses && rhs ) MAX_DOES_NOT_THROW
	{
		EndPoints = rhs.EndPoints;
		rhs.EndPoints = NULL;
		return *this;
	}

	AddressesIterator Addresses::begin() const MAX_DOES_NOT_THROW
	{
		return AddressesIterator( EndPoints );
	}

	AddressesIterator Addresses::end() const MAX_DOES_NOT_THROW
	{
		return AddressesIterator( NULL );
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
