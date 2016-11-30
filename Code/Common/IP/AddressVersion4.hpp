// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP
#define MAXSOCKET_IP_ADDRESSVERSION4_HPP

#include <maxSocket/IP/Address.hpp>
#include <max/Compiling/Configuration/Platform.hpp>
#include <max/Compiling/ThrowSpecification.hpp>
#include <max/Compiling/VirtualFunctionSpecification.hpp>
#if defined(MAX_PLATFORM_WINDOWS)
	#include "../../Windows/WindowsAddressVersion4Policy.hpp"
#endif
#if defined(MAX_PLATFORM_LINUX)
	#include "../../Linux/LinuxAddressVersion4Policy.hpp"
#endif
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace IP
{

	template< typename NativeAddressPolicy >
	class PlatformIndependentAddressVersion4;

	#if defined(MAX_PLATFORM_WINDOWS)
		typedef PlatformIndependentAddressVersion4< WindowsAddressVersion4Policy > AddressVersion4;
	#endif
	#if defined(MAX_PLATFORM_LINUX)
		typedef PlatformIndependentAddressVersion4< LinuxAddressVersion4Policy > AddressVersion4;
	#endif

	template< typename NativeAddressPolicy >
	class PlatformIndependentAddressVersion4 : public v0::IP::Address
	{
	public:

		explicit PlatformIndependentAddressVersion4( NativeAddressPolicy policy ) MAX_DOES_NOT_THROW;
		MAX_OVERRIDE( ~PlatformIndependentAddressVersion4() MAX_DOES_NOT_THROW );

		MAX_OVERRIDE( std::string GetRepresentation() const MAX_DOES_NOT_THROW );

		NativeAddressPolicy m_NativeAddressPolicy;

	}; // class PlatformIndependentAddressVersion4

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#include "AddressVersion4.inl"

#endif // #ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP
