// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_TESTING_TEST_HPP
#define MAX_TESTING_TEST_HPP

#include <string>
#include <functional>

#define MAX_TESTING_ASSERT( CONDITION ) \
	Assert( __FILE__, __LINE__, #CONDITION, CONDITION )

#define MAX_TESTING_ASSERT_THROWS( FUNCTOR ) \
	AssertThrows( __FILE__, __LINE__, #FUNCTOR, FUNCTOR )

#define MAX_TESTING_ASSERT_DOES_NOT_THROW( FUNCTOR ) \
	AssertDoesNotThrow( __FILE__, __LINE__, #FUNCTOR, FUNCTOR )

namespace max
{
namespace Testing
{

	class Test
	{
	public:

		Test( char const * const Name, std::function< void( max::Testing::Test & CurrentTest ) > const & TestFunction  );

		bool DidTestPass() const;

		void Assert( char const * const FileName, int LineNumber, char const * const ExpressionString, bool Expression );

		template< typename ExceptionType, typename FunctorType >
		void AssertThrows( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor );

		template< typename ExceptionType, typename FunctorType >
		void AssertDoesNotThrow( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor );


		const std::string Name;
		std::function< void( max::Testing::Test & CurrentTest ) > TestFunction;

	private:

		bool DidAllAssertionsPass;

	};

} // namespace Testing
} // namespace max

#endif // #ifndef MAX_TESTING_TEST_HPP
