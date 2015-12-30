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
