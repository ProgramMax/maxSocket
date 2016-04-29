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

#ifndef MAX_TESTING_TEST_HPP
#define MAX_TESTING_TEST_HPP

#include <string>
#include <functional>

#define MAX_TESTING_ASSERT( CONDITION ) \
	Assert( __FILE__, __LINE__, #CONDITION, CONDITION );

#define MAX_TESTING_ASSERT_THROWS( FUNCTOR ) \
	AssertThrows( __FILE__, __LINE__, #FUNCTOR, FUNCTOR );

#define MAX_TESTING_ASSERT_DOES_NOT_THROW( FUNCTOR ) \
	AssertDoesNotThrow( __FILE__, __LINE__, #FUNCTOR, FUNCTOR );

namespace max
{
namespace Testing
{

	class Test
	{
	public:

		Test( wchar_t const * const Name, std::function< void( max::Testing::Test & CurrentTest ) > const & TestFunction  );

		bool DidTestPass() const;

		void Assert( char const * const FileName, int LineNumber, char const * const ExpressionString, bool Expression );

		template< typename ExceptionType, typename FunctorType >
		void AssertThrows( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor );

		template< typename ExceptionType, typename FunctorType >
		void AssertDoesNotThrow( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor );


		const std::wstring Name;
		std::function< void( max::Testing::Test & CurrentTest ) > TestFunction;

	private:

		bool DidAllAssertionsPass;

	};

} // namespace Testing
} // namespace max

#endif // #ifndef MAX_TESTING_TEST_HPP
