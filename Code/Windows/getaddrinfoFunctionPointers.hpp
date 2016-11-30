// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
