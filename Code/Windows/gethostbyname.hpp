// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_GETHOSTBYNAME_HPP
#define MAXSOCKET_GETHOSTBYNAME_HPP

#include "ResolveHostNameImplementationInterface.hpp"
#include <max/Compiling/VirtualFunctionSpecification.hpp>

namespace maxSocket
{

	class gethostbyname : public ResolveHostNameImplementationInterface
	{
	public:

		MAX_OVERRIDE( ~gethostbyname() MAX_DOES_NOT_THROW );

		MAX_OVERRIDE( ResolveHostNameResults::Enum ResolveHostName( const char * const HostName,
		                                                            const AddressFamily::Enum AddressFamilyFilter,
		                                                            std::vector< std::unique_ptr< v0::IP::Address > > & EndPoints,
		                                                            const int MaximumEndPointSanityCheck
		                                                          ) MAX_DOES_NOT_THROW );

	}; // class gethostbyname

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_GETHOSTBYNAME_HPP
