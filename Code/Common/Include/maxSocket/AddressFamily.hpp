// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_ADDRESSFAMILY_HPP
#define MAXSOCKET_ADDRESSFAMILY_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{

	namespace AddressFamily
	{
		enum Enum
		{
			IPv4,
			IPv6,
			Any
		};

	} // namespace AddressFamily

} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // nameSpace maxSocket

#endif // #ifndef MAXSOCKET_ADDRESSFAMILY_HPP
