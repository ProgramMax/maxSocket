// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_IP_ADDRESS_HPP
#define MAXSOCKET_IP_ADDRESS_HPP

#include "Version.hpp"
#include <max/Compiling/ThrowSpecification.hpp>
#include <string>
#include <max/Compiling/CurrentVersionNamespace.hpp>
#include "AddressVersion4.hpp"
#include "AddressVersion6.hpp"
#include <new>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace IP
{

	class Address
	{
	public:

		explicit Address( AddressVersion4 Version4Address ) MAX_DOES_NOT_THROW;
		explicit Address( AddressVersion6 Version6Address ) MAX_DOES_NOT_THROW;

		~Address() MAX_DOES_NOT_THROW;

		std::string GetRepresentation() const MAX_DOES_NOT_THROW;

		const Version::Enum m_Version;
		union UnderlyingRepresentation
		{
			AddressVersion4 Version4Address;
			AddressVersion6 Version6Address;

			explicit UnderlyingRepresentation( const AddressVersion4 & Version4Address )
			{
				new ( & this->Version4Address ) AddressVersion4( Version4Address );
			}
			explicit UnderlyingRepresentation( AddressVersion4 && Version4Address )
			{
				new ( & this->Version4Address ) AddressVersion4( std::move( Version4Address ) );
			}
			explicit UnderlyingRepresentation( const AddressVersion6 & Version6Address )
			{
				new ( & this->Version6Address ) AddressVersion6( Version6Address );
			}
			explicit UnderlyingRepresentation( AddressVersion6 && Version6Address )
			{
				new ( & this->Version6Address ) AddressVersion6( std::move( Version6Address ) );
			}
		};
		UnderlyingRepresentation AddressRepresentation;

	}; // class Address

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_IP_ADDRESS_HPP
