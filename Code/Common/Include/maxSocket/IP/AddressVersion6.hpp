// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_IP_ADDRESSVERSION6_HPP
#define MAXSOCKET_IP_ADDRESSVERSION6_HPP

#include <max/Compiling/ThrowSpecification.hpp>
#include <string>
#include <max/Compiling/CurrentVersionNamespace.hpp>
#if defined(MAX_PLATFORM_LINUX)
	#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
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

	#if defined(MAX_PLATFORM_LINUX)
		typedef sockaddr_in6 NativeIPVersion6AddressType;
	#endif
	#if defined(MAX_PLATFORM_WINDOWS)
		typedef in_addr6     NativeIPVersion6AddressType;
	#endif

	class AddressVersion6
	{
	public:

		AddressVersion6() = delete;
		AddressVersion6( const AddressVersion6 & rhs ) MAX_DOES_NOT_THROW = default;
		AddressVersion6( AddressVersion6 && rhs ) MAX_DOES_NOT_THROW = default;
		explicit AddressVersion6( const NativeIPVersion6AddressType NativeIPVersion6Address ) MAX_DOES_NOT_THROW;

		~AddressVersion6() MAX_DOES_NOT_THROW = default;

		AddressVersion6 & operator =( const AddressVersion6 & rhs ) MAX_DOES_NOT_THROW = default;
		AddressVersion6 & operator =( AddressVersion6 && rhs ) MAX_DOES_NOT_THROW = default;

		std::string GetRepresentation() const MAX_DOES_NOT_THROW;

	//private:

		NativeIPVersion6AddressType NativeIPVersion6Address;

	}; // class AddressVersion6

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_IP_ADDRESSVERSION6_HPP
