// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_RESOLVEHOSTNAMEIMPLEMENTATIONINTERFACE_HPP
#define MAXSOCKET_RESOLVEHOSTNAMEIMPLEMENTATIONINTERFACE_HPP

#include <max/Compiling/ThrowSpecification.hpp>
#include <maxSocket/AddressFamily.hpp>
#include <vector>
#include <memory>
#include <maxSocket/IP/Address.hpp>
#include <maxSocket/SocketSystem.hpp>

namespace maxSocket
{

	class ResolveHostNameImplementationInterface
	{
	public:

		virtual ~ResolveHostNameImplementationInterface() MAX_DOES_NOT_THROW;

		virtual ResolveHostNameResults::Enum ResolveHostName( char const * const HostName,
		                                                      const AddressFamily::Enum AddressFamilyFilter,
		                                                      std::vector< std::unique_ptr< v0::IP::Address > > & EndPoints,
		                                                      const int MaximumEndPointSanityCheck
		                                                    ) MAX_DOES_NOT_THROW = 0;

	}; // class ResolveHostNameImplementationInterface

} // namespace maxsocket

#endif // #ifndef MAXSOCKET_RESOLVEHOSTNAMEIMPLEMENTATIONINTERFACE_HPP
