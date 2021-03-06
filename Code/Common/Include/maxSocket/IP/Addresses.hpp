// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include "AddressesIterator.hpp"
#if defined(MAX_PLATFORM_LINUX)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <unistd.h>
#endif
#if defined(MAX_PLATFORM_WINDOWS)
	#include <Ws2tcpip.h>
#endif

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace IP
{

	class Addresses
	{
	public:

		Addresses() MAX_DOES_NOT_THROW;
		Addresses( const Addresses & rhs ) MAX_DOES_NOT_THROW = delete;
		Addresses( Addresses && rhs ) MAX_DOES_NOT_THROW;
		explicit Addresses( addrinfo * LinuxEndPoints ) MAX_DOES_NOT_THROW;

		~Addresses() MAX_DOES_NOT_THROW;

		Addresses & operator =( const Addresses & rhs ) MAX_DOES_NOT_THROW = delete;
		Addresses & operator =( Addresses && rhs ) MAX_DOES_NOT_THROW;

		AddressesIterator begin() const MAX_DOES_NOT_THROW;
		AddressesIterator end() const MAX_DOES_NOT_THROW;

	private:

		addrinfo * EndPoints;

	};

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket
