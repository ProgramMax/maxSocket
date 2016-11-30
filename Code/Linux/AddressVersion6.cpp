// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
