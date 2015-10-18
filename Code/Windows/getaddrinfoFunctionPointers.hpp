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

#ifndef MAXSOCKET_GETADDRINFOPARAMS_HPP
#define MAXSOCKET_GETADDRINFOPARAMS_HPP

#ifdef NO_PRECOMPILED_HEADER
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>

	#include <Ws2tcpip.h>
#else
	#include "PrecompiledHeader.hpp"
#endif
#include <max/Compiling/ThrowSpecification.hpp>
#include <memory>

namespace maxSocket
{

	namespace CreategetaddrinfoFunctionPointersResults
	{
		enum Enum
		{
			Success,
			getaddrinfoNotSupported,
			UnknownError
		}; // enum Enum
	} // namespace CreategetaddrinfoFunctionPointersResults

	class getaddrinfoFunctionPointers
	{
	public:

		typedef int ( WSAAPI * getaddrinfoFunctionType )( const char *     pNodeName,
		                                                  const char *     pServiceName,
		                                                  const addrinfo * pHints,
		                                                  addrinfo * *     ppResult );
		typedef void ( WSAAPI * freeaddrinfoFunctionType )( addrinfo * ai );


		getaddrinfoFunctionPointers( const getaddrinfoFunctionType getaddrinfo,
		                             const freeaddrinfoFunctionType freeaddrinfo,
		                             const HMODULE WS232Handle
		                           ) MAX_DOES_NOT_THROW;

		~getaddrinfoFunctionPointers() MAX_DOES_NOT_THROW;

		

		const getaddrinfoFunctionType getaddrinfo;
		const freeaddrinfoFunctionType freeaddrinfo;

	private:

		const HMODULE WS232Handle;

		friend CreategetaddrinfoFunctionPointersResults::Enum CreategetaddrinfoParams( std::unique_ptr< getaddrinfoFunctionPointers > & FunctionPointers ) MAX_DOES_NOT_THROW;

	};

	CreategetaddrinfoFunctionPointersResults::Enum CreategetaddrinfoParams( std::unique_ptr< getaddrinfoFunctionPointers > & FunctionPointers ) MAX_DOES_NOT_THROW;

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_GETADDRINFOPARAMS_HPP