// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include <maxSocket/IP/AddressVersion4.hpp>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace maxSocket
{
namespace v0
{
namespace IP
{

	AddressVersion4::AddressVersion4( const NativeIPVersion4AddressType NativeIPVersion4Address ) MAX_DOES_NOT_THROW
		: NativeIPVersion4Address( NativeIPVersion4Address )
	{
	}

	std::string AddressVersion4::GetRepresentation() const MAX_DOES_NOT_THROW
	{
		auto & Address = NativeIPVersion4Address.sin_addr;
		char str[ INET_ADDRSTRLEN ];
		return std::string( inet_ntop( AF_INET, & Address, str, INET_ADDRSTRLEN ) );
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
