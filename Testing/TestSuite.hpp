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

#ifndef MAX_TESTING_TESTSUITE_HPP
#define MAX_TESTING_TESTSUITE_HPP

// Usage:
//
// #include <max/Testing/TestSuite.hpp>
// #incldue <stdexcept>
//
// int main() {
//   max::Testing::TestSuite( "Example suite",
//     max::Testing::AddTest( "Test equality",
//       []( auto const & CurrentTestSuite ) {
//         CurrentTestSuite.AssertEquals( 1, 1 );
//       }
//     ),
//     max::Testing::AddTest( "Test throws",
//       []( auto const & CurrentTestSuite ) {
//         CurrentTestSuite.assertThrows< std::exception >(
//           []() { throw std::exception{}; }
//         );
//       }
//     )
//   );
// }

#include <max/Testing/Test.hpp>

namespace max
{
namespace Testing
{

	template< typename FunctorType >
	Test< FunctorType > AddTest( const wchar_t * Name, FunctorType const & Functor );

	class TestSuite
	{
	private:

		mutable bool CurrentTestFailed;

	public:

		template< typename... TestFunctor >
		TestSuite( const wchar_t * Name, Test< TestFunctor > &&... Tests );


		void Assert( const bool Expression ) const;

		template< typename T, typename U >
		void AssertEqualTo( T const & lhs, U const & rhs ) const;

		template< typename T, typename U >
		void AssertLessThan( T const & lhs, U const & rhs ) const;

		template< typename T, typename U >
		void AssertGreaterThan( T const & lhs, U const & rhs ) const;

		template< typename T, typename U >
		void AssertLessThanOrEqualTo( T const & lhs, U const & rhs ) const;

		template< typename T, typename U >
		void AssertGreaterThanOrEqualTo( T const & lhs, U const & rhs ) const;

		template< typename ExceptionType, typename FunctorType >
		void AssertThrows( FunctorType const & Functor ) const;

		template< typename ExceptionType, typename FunctorType >
		void AssertDoesNotThrow( FunctorType const & Functor ) const;

		virtual void Setup() const;
		virtual void TearDown() const;

	};

} // namespace Testing
} // namespace max

#include "TestSuite.inl"

#endif // #ifndef MAX_TESTING_TESTSUITE_HPP