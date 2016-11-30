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
