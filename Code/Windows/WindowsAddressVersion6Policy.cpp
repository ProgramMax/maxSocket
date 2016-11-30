// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include "WindowsAddressVersion6Policy.hpp"

namespace maxSocket
{
namespace IP
{

	WindowsAddressVersion6Policy::WindowsAddressVersion6Policy( in_addr6 Address ) MAX_DOES_NOT_THROW
		: m_Address( Address )
	{
	}

	std::string WindowsAddressVersion6Policy::GetRepresentation() MAX_DOES_NOT_THROW
	{
		char str[ INET6_ADDRSTRLEN ];
		return std::string( inet_ntop( AF_INET6, & m_Address, str, INET6_ADDRSTRLEN ) );
	}

} // namespace IP
} // namespace maxSocket
