// Copyright 2015, Chris Blume
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Chris Blume nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP
#define MAXSOCKET_IP_ADDRESSVERSION4_HPP

#include <maxSocket/IP/Address.hpp>
#include <max/Compiling/Configuration/Platform.hpp>
#ifndef NO_PRECOMPILED_HEADER
	#include "../../Windows/PrecompiledHeader.hpp"
#endif // #ifndef NO_PRECOMPILED_HEADER
#include <max/Compiling/ThrowSpecification.hpp>
#include <max/Compiling/VirtualFunctionSpecification.hpp>
#if defined(MAX_PLATFORM_WINDOWS)
	#include "../../Windows/WindowsAddressVersion4Policy.hpp"
#endif
#if defined(MAX_PLATFORM_LINUX)
	#include "../../Linux/LinuxAddressVersion4Policy.hpp"
#endif

namespace maxSocket
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
	class PlatformIndependentAddressVersion4 : public Address
	{
	public:

		explicit PlatformIndependentAddressVersion4( NativeAddressPolicy policy ) MAX_DOES_NOT_THROW;
		MAX_OVERRIDE( ~PlatformIndependentAddressVersion4() MAX_DOES_NOT_THROW );

		MAX_OVERRIDE( std::string GetRepresentation() MAX_DOES_NOT_THROW );

		NativeAddressPolicy m_NativeAddressPolicy;

	}; // class PlatformIndependentAddressVersion4

} // namespace IP
} // namespace maxSocket

#include "AddressVersion4.inl"

#endif // #ifndef MAXSOCKET_IP_ADDRESSVERSION4_HPP