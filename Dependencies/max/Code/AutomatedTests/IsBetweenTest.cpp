// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "IsBetweenTest.hpp"
#include <max/Algorithms/IsBetween.hpp>
#include <max/Testing/TestSuite.hpp>

namespace maxAutomatedTests
{
namespace Algorithms
{

	void RunIsBetweenTestSuite()
	{
		auto IsBetweenTestSuite = max::Testing::TestSuite{ "max::Algorithms::IsBetween test suite" };
		
		IsBetweenTestSuite.AddTest( max::Testing::Test{ "inside range", []( max::Testing::Test & CurrentTest ) {
			CurrentTest.MAX_TESTING_ASSERT( max::Algorithms::IsBetween( 10, { 1, 100 } ) );
		}
		} );

		IsBetweenTestSuite.AddTest( max::Testing::Test{ "before range", []( max::Testing::Test & CurrentTest ) {
			CurrentTest.MAX_TESTING_ASSERT( ! max::Algorithms::IsBetween( 0, { 1, 100 } ) );
		}
		} );

		IsBetweenTestSuite.AddTest( max::Testing::Test{ "after range", []( max::Testing::Test & CurrentTest ) {
			CurrentTest.MAX_TESTING_ASSERT( ! max::Algorithms::IsBetween( 200, { 1, 100 } ) );
		}
		} );

		IsBetweenTestSuite.AddTest( max::Testing::Test{ "minimum and maximum switched", []( max::Testing::Test & CurrentTest ) {
			CurrentTest.MAX_TESTING_ASSERT( ! max::Algorithms::IsBetween( 10, { 100, 1 } ) );
		}
		} );

		IsBetweenTestSuite.RunTests();
	}

} // namespace Algorithms
} // namespace maxAutomatedTests