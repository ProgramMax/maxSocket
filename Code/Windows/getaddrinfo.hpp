// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_GETADDRINFO_HPP
#define MAXSOCKET_GETADDRINFO_HPP

#include "ResolveHostNameImplementationInterface.hpp"
#include <max/Compiling/VirtualFunctionSpecification.hpp>
#include "getaddrinfoFunctionPointers.hpp"

namespace maxSocket
{

	class getaddrinfo : public ResolveHostNameImplementationInterface
	{
	public:

		explicit getaddrinfo( const getaddrinfoFunctionPointers & FunctionPointers ) MAX_DOES_NOT_THROW;

		MAX_OVERRIDE( ~getaddrinfo() MAX_DOES_NOT_THROW );

		MAX_OVERRIDE( ResolveHostNameResults::Enum ResolveHostName( char const * const HostName,
                                              const AddressFamily::Enum AddressFamilyFilter,
                                              std::vector< std::unique_ptr< v0::IP::Address > > & EndPoints,
		                                      const int MaximumEndPointSanityCheck
                                            ) MAX_DOES_NOT_THROW );

	private:

		const getaddrinfoFunctionPointers FunctionPointers;

	}; // class getaddrinfo

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_GETADDRINFO_HPP
