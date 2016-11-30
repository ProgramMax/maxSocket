// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_ADDRESSESITERATOR_HPP
#define MAXSOCKET_ADDRESSESITERATOR_HPP

#include <iterator>
#include <memory>
#include <maxSocket/IP/Address.hpp>
#if defined(MAX_PLATFORM_LINUX)
	#include <netdb.h>
	//#include <arpa/inet.h>
#endif
#if defined(MAX_PLATFORM_WINDOWS)
	#include <Ws2tcpip.h>
#endif
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace IP
{

	class AddressesIterator : public std::iterator< std::forward_iterator_tag, maxSocket::v0::IP::Address >
	{
	public:

		AddressesIterator() = delete;
		AddressesIterator( const AddressesIterator & rhs ) = default;
		AddressesIterator( AddressesIterator && rhs )      = default;

		AddressesIterator & operator =( const AddressesIterator & rhs ) = default;
		AddressesIterator & operator =( AddressesIterator && rhs )      = default;

		AddressesIterator & operator ++();
		AddressesIterator   operator ++( int );

		bool operator ==( const AddressesIterator & rhs ) const;
		bool operator !=( const AddressesIterator & rhs ) const;

		maxSocket::v0::IP::Address operator *() const;

	private:

		friend class Addresses;

		explicit AddressesIterator( addrinfo * const CurrentEndPoint );

		addrinfo * CurrentEndPoint;

	}; // class AddressesIterator

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_ADDRESSESITERATOR_HPP