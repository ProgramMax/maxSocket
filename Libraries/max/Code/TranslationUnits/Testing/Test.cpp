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

#include "max/Testing/Test.hpp"
#include <iostream>

namespace max
{
namespace Testing
{

	Test::Test( wchar_t const * const Name, std::function< void( max::Testing::Test & CurrentTest ) > const & TestFunction )
		: Name( Name )
		, TestFunction( TestFunction )
		, DidAllAssertionsPass( true )
	{
	}

	bool Test::DidTestPass() const
	{
		return DidAllAssertionsPass;
	}

	void Test::Assert( char const * const FileName, int LineNumber, char const * const ExpressionString, bool const Expression )
	{
		bool const AssertionPassed = Expression;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			std::wcout << L"Assert failed: " << ExpressionString << "\n";
			std::wcout << L"\tin file " << FileName << "\n";
			std::wcout << L"\ton line " << LineNumber << std::endl;
		}
	}

	template< typename ExceptionType, typename FunctorType >
	void Test::AssertThrows( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor )
	{
		bool ThrewExpectedType = false;
		try
		{
			Functor();
		}
		catch( ExceptionType & )
		{
			ThrewExpectedType = true;
		}
		catch( ... )
		{
		}

		bool const AssertionPassed = ThrewExpectedType;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			std::wcout << L"Assertion failed: " << ExpressionString << "\n";
			std::wcout << L"\tin file " << FileName << "\n";
			std::wcout << L"\ton line " << LineNumber << std::endl;
		}
	}

	template< typename ExceptionType, typename FunctorType >
	void Test::AssertDoesNotThrow( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor )
	{
		bool ThrewUnexpectedType = false;
		try
		{
			Functor();
		}
		catch( ExceptionType & )
		{
			ThrewUnexpectedType = true;
		}
		catch( ... )
		{
		}

		bool const AssertionPassed = ! ThrewUnexpectedType;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			std::wcout << L"Assertion failed: " << ExpressionString << "\n";
			std::wcout << L"\tin file " << FileName << "\n";
			std::wcout << L"\ton line " << LineNumber << std::endl;
		}
	}

} // namespace Testing
} // namespace max
