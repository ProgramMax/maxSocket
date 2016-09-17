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

#include <maxSocket/IP/AddressVersion6.hpp>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	AddressVersion6::AddressVersion6( const NativeIPVersion6AddressType NativeIPVersion6Address ) MAX_DOES_NOT_THROW
		: NativeIPVersion6Address( NativeIPVersion6Address )
	{
	}

	std::string AddressVersion6::GetRepresentation() const MAX_DOES_NOT_THROW
	{
		auto & Address = NativeIPVersion6Address.sin6_addr;
		char str[ INET6_ADDRSTRLEN ];
		return std::string( inet_ntop( AF_INET6, & Address, str, INET6_ADDRSTRLEN ) );
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
