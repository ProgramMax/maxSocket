// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include "WindowsAddressVersion4Policy.hpp"
#include <max/Compiling/ThrowSpecification.hpp>

namespace maxSocket
{
namespace IP
{

	WindowsAddressVersion4Policy::WindowsAddressVersion4Policy( in_addr Address ) MAX_DOES_NOT_THROW
		: m_Address( Address )
	{
	}

	std::string WindowsAddressVersion4Policy::GetRepresentation() MAX_DOES_NOT_THROW
	{
		char str[ INET_ADDRSTRLEN ];
		return std::string( inet_ntop( AF_INET, & m_Address, str, INET_ADDRSTRLEN ) );
	}

} // namespace IP
} // namespace maxSocket
