// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "max/Testing/Test.hpp"
#include <iostream>

namespace max
{
namespace Testing
{

	Test::Test( char const * const Name, std::function< void( max::Testing::Test & CurrentTest ) > const & TestFunction )
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