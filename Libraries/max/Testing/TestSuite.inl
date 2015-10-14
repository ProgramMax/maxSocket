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

#include <iostream>
#include <max/Compiling/UnreferencedValue.hpp>

namespace
{

	template< typename FunctorType, typename... ArgsTypes >
	void ForEachVariadic( FunctorType const & Functor, ArgsTypes &&... Args )
	{
		using Swallow = unsigned[];
		Swallow _ {
			(
				Functor( std::forward< decltype( Args ) >( Args ) ),
				0u
			)...
		};
		max::Compiling::UnreferencedValue( _ );
	};

	void PrintTestResult( const bool CurrentTestFailed, wchar_t const * const AssertExpression )
	{
		if( CurrentTestFailed )
		{
			std::wcout << L"Failed" << std::endl;
			std::wcout << L"\t" << AssertExpression << std::endl;
		} else {
			std::wcout << L"Passed" << std::endl;
		}
	}

	template< typename lhsType, typename rhsType >
	void PrintTestResult( const bool CurrentTestFailed, wchar_t const * const AssertExpression, const lhsType & lhs, const rhsType & rhs )
	{
		if( CurrentTestFailed )
		{
			std::wcout << L"Failed" << std::endl;
			std::wcout << L"\t" << AssertExpression << std::endl;
			std::wcout << L"\tlhs = " << lhs << std::endl;
			std::wcout << L"\trhs = " << rhs << std::endl;
		} else {
			std::wcout << "Passed" << std::endl;
		}
	}

} // unnamed namespace

namespace max
{
namespace Testing
{

	template< typename FunctorType >
	Test< FunctorType > AddTest( const wchar_t * Name, FunctorType const & Functor )
	{
		return max::Testing::Test< FunctorType >( Name, Functor );
	}

	template< typename... TestFunctor >
	TestSuite::TestSuite( const wchar_t * Name, Test< TestFunctor > &&... Tests )
	{
		std::wcout << L"Running test suite: " << Name << std::endl;

		Setup();

		ForEachVariadic(
			[ this ]( auto & CurrentTest ) {
				CurrentTestFailed = false;

				std::wcout << L"Running test " << CurrentTest.Name << L" ... ";
				CurrentTest.TestFunction( * this );
			},
			Tests...
		);

		TearDown();
	}

	void TestSuite::Assert( const bool Expression ) const
	{
		CurrentTestFailed = ! Expression;
		PrintTestResult( CurrentTestFailed, L"Assert( Expression );" );
	}

	template< typename T, typename U >
	void TestSuite::AssertEqualTo( T const & lhs, U const & rhs ) const
	{
		const bool AssertPassed = lhs == rhs;
		CurrentTestFailed = ! AssertPassed;
		PrintTestResult( CurrentTestFailed, L"AssertEqualTo( lhs, rhs );", lhs, rhs );
	}

	template< typename T, typename U >
	void TestSuite::AssertLessThan( T const & lhs, U const & rhs ) const
	{
		const bool AssertPassed = lhs < rhs;
		CurrentTestFailed = ! AssertPassed;
		PrintTestResult( CurrentTestFailed, L"AssertLessThan( lhs, rhs );", lhs, rhs );
	}

	template< typename T, typename U >
	void TestSuite::AssertGreaterThan( T const & lhs, U const & rhs ) const
	{
		const bool AssertPassed = lhs > rhs;
		CurrentTestFailed = ! AssertPassed;
		PrintTestResult( CurrentTestFailed, L"AssertGreaterThan( lhs, rhs );", lhs, rhs );
	}

	template< typename T, typename U >
	void TestSuite::AssertLessThanOrEqualTo( T const & lhs, U const & rhs ) const
	{
		const bool AssertPassed = lhs <= rhs;
		CurrentTestFailed = ! AssertPassed;
		PrintTestResult( CurrentTestFailed, L"AssertLessThanOrEqualTo( lhs, rhs );", lhs, rhs );
	}

	template< typename T, typename U >
	void TestSuite::AssertGreaterThanOrEqualTo( T const & lhs, U const & rhs ) const
	{
		const bool AssertPassed = lhs >= rhs;
		CurrentTestFailed = ! AssertPassed;
		PrintTestResult( CurrentTestFailed, L"AssertGreaterThanOrEqualTo( lhs, rhs );", lhs, rhs );
	}

	template< typename ExceptionType, typename FunctorType >
	void TestSuite::AssertThrows( FunctorType const & Functor ) const
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

		CurrentTestFailed = ! ThrewExpectedType;
		PrintTestResult( CurrentTestFailed, L"AssertThrows( ... );" );
	}

	template< typename ExceptionType, typename FunctorType >
	void TestSuite::AssertDoesNotThrow( FunctorType const & Functor ) const
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

		CurrentTestFailed = ThrewUnexpectedType;
		PrintTestResult( CurrentTestFailed, L"AssertDoesNotThrow( ... );" );
	}

	void TestSuite::Setup() const
	{
	}

	void TestSuite::TearDown() const
	{
	}

} // namespace Testing
} // namespace max
