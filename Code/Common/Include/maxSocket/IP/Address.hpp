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

#ifndef MAXSOCKET_IP_ADDRESS_HPP
#define MAXSOCKET_IP_ADDRESS_HPP

#include "Version.hpp"
#ifndef NO_PRECOMPILED_HEADER
	#include "../../../../Windows/PrecompiledHeader.hpp"
#endif // #ifndef NO_PRECOMPILED_HEADER
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
