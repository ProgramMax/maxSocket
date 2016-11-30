// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP
#define MAXSOCKET_IP_ADDRESSVERSION4_HPP

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
		typedef sockaddr_in NativeIPVersion4AddressType;
	#endif
	#if defined(MAX_PLATFORM_WINDOWS)
		typedef in_addr     NativeIPVersion4AddressType;
	#endif

	class AddressVersion4
	{
	public:

		AddressVersion4() = delete;
		AddressVersion4( const AddressVersion4 & rhs ) MAX_DOES_NOT_THROW = default;
		AddressVersion4( AddressVersion4 && rhs ) MAX_DOES_NOT_THROW = default;
		explicit AddressVersion4( const NativeIPVersion4AddressType NativeIPVersion4Address ) MAX_DOES_NOT_THROW;

		~AddressVersion4() MAX_DOES_NOT_THROW = default;

		AddressVersion4 & operator =( const AddressVersion4 & rhs ) MAX_DOES_NOT_THROW = default;
		AddressVersion4 & operator =( AddressVersion4 && rhs ) MAX_DOES_NOT_THROW = default;

		std::string GetRepresentation() const MAX_DOES_NOT_THROW;

	//private:

		NativeIPVersion4AddressType NativeIPVersion4Address;

	}; // class AddressVersion4

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP
