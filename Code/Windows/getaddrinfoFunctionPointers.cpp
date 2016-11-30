// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
