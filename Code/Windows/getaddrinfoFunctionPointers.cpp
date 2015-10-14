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

#include "PrecompiledHeader.hpp"
#include "getaddrinfoFunctionPointers.hpp"
#include <max/Algorithms/ScopedFunctor.hpp>

namespace maxSocket
{

	getaddrinfoFunctionPointers::getaddrinfoFunctionPointers( const getaddrinfoFunctionType getaddrinfo,
	                                                          const freeaddrinfoFunctionType freeaddrinfo,
	                                                          const HMODULE WS232Handle
	                                                        ) MAX_DOES_NOT_THROW
		: getaddrinfo( getaddrinfo )
		, freeaddrinfo( freeaddrinfo )
		, WS232Handle( WS232Handle )
	{
	}

	getaddrinfoFunctionPointers::~getaddrinfoFunctionPointers() MAX_DOES_NOT_THROW
	{
		FreeLibrary( WS232Handle );
	}

	CreategetaddrinfoFunctionPointersResults::Enum CreategetaddrinfoParams( std::unique_ptr< getaddrinfoFunctionPointers > & FunctionPointers ) MAX_DOES_NOT_THROW
	{
		auto WS232Handle = LoadLibrary( TEXT( "Ws2_32.dll" ) );
		if( WS232Handle == NULL )
		{
			return CreategetaddrinfoFunctionPointersResults::getaddrinfoNotSupported;
		}

		{
			auto CleanupWinsockLibrary = max::Algorithms::MakeScopedFunctor( [WS232Handle]() { FreeLibrary( WS232Handle ); } ); 
			FARPROC getaddrinfoProcedure = GetProcAddress( WS232Handle, "getaddrinfo" );
			if( getaddrinfoProcedure == NULL )
			{
				auto ErrorCode = GetLastError();
				if( ErrorCode == 127 ) // The specified procedure could not be found.
				{
					return CreategetaddrinfoFunctionPointersResults::getaddrinfoNotSupported;
				} else {
					return CreategetaddrinfoFunctionPointersResults::UnknownError;
				}
			}
			auto getaddrinfo = reinterpret_cast< getaddrinfoFunctionPointers::getaddrinfoFunctionType >( getaddrinfoProcedure );


			FARPROC freeaddrinfoProcedure = GetProcAddress( WS232Handle, "freeaddrinfo" );
			if( freeaddrinfoProcedure == NULL )
			{
				auto ErrorCode = GetLastError();
				if( ErrorCode == 127 ) // The specified procedure could not be found.
				{
					return CreategetaddrinfoFunctionPointersResults::getaddrinfoNotSupported;
				} else {
					return CreategetaddrinfoFunctionPointersResults::UnknownError;
				}
			}
			auto freeaddrinfo = reinterpret_cast< getaddrinfoFunctionPointers::freeaddrinfoFunctionType >( freeaddrinfoProcedure );
	

			auto DuplicatedHandle = static_cast< HMODULE >( INVALID_HANDLE_VALUE );
			auto GetModuleHandleExResult = GetModuleHandleEx( 0, TEXT( "Ws2_32.dll" ), & DuplicatedHandle );
			if( GetModuleHandleExResult == 0 )
			{
				//auto ErrorCode = GetLastError();
			}

			FunctionPointers = std::make_unique< getaddrinfoFunctionPointers >( getaddrinfo, freeaddrinfo, static_cast< HMODULE >( DuplicatedHandle ) );

			return CreategetaddrinfoFunctionPointersResults::Success;
		}
	}

} // namespace maxSocket
