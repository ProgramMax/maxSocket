// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "RangeTest.hpp"
#include <max/Containers/Range.hpp>
#include <max/Testing/TestSuite.hpp>

namespace maxAutomatedTests
{
namespace Containers
{

	void RunRangeTestSuite()
	{
		static_assert( max::Containers::Range< int >{ 0, 1 }.Maximum == 1, "max::Containers::Range ctor should be constexpr" );


		auto RangeTestSuite = max::Testing::TestSuite{ "max::Containers::Range test suite" };

		RangeTestSuite.AddTest( max::Testing::Test{ "constructor sets minimum and maximum correctly", []( max::Testing::Test & CurrentTest ) {
			auto testRange = max::Containers::Range< int >{ 42, 100 };
			CurrentTest.MAX_TESTING_ASSERT( testRange.Minimum == 42  );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Maximum == 100 );
		}
		} );

		RangeTestSuite.AddTest( max::Testing::Test{ "constructor accepts same values", []( max::Testing::Test & CurrentTest ) {
			auto testRange = max::Containers::Range< int >{ 42, 42 };
			CurrentTest.MAX_TESTING_ASSERT( testRange.Minimum == 42 );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Maximum == 42 );
		}
		} );

		RangeTestSuite.AddTest( max::Testing::Test{ "MakeRange with minimum first", []( max::Testing::Test & CurrentTest ) {
			auto testRange = max::Containers::MakeRange( 1, 42 );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Minimum == 1  );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Maximum == 42 );
		}
		} );

		RangeTestSuite.AddTest( max::Testing::Test{ "MakeRange with maximum first", []( max::Testing::Test & CurrentTest ) {
 			auto testRange = max::Containers::MakeRange( 100, 42 );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Minimum == 42  );
			CurrentTest.MAX_TESTING_ASSERT( testRange.Maximum == 100 );
		}
		} );

		RangeTestSuite.RunTests();
	}

} // namespace Containers
} // namespace maxAutomatedTests
