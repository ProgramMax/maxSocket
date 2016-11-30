// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxSocket/IP/Address.hpp>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	Address::Address( AddressVersion4 Version4Address ) MAX_DOES_NOT_THROW
		: m_Version( Version::Version4 )
		, AddressRepresentation( Version4Address )
	{
	}

	Address::Address( AddressVersion6 Version6Address ) MAX_DOES_NOT_THROW
		: m_Version( Version::Version6 )
		, AddressRepresentation( Version6Address )
	{
	}

	Address::~Address() MAX_DOES_NOT_THROW
	{
		switch( m_Version )
		{
		case Version::Version4:
			AddressRepresentation.Version4Address.~AddressVersion4();
			break;
		case Version::Version6:
			AddressRepresentation.Version6Address.~AddressVersion6();
			break;
		}
	}

	std::string Address::GetRepresentation() const MAX_DOES_NOT_THROW
	{
		switch( m_Version )
		{
		case Version::Version4:
			return AddressRepresentation.Version4Address.GetRepresentation();
		case Version::Version6:
			return AddressRepresentation.Version6Address.GetRepresentation();
		}
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
