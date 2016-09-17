// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "AliasingOptimizationsTest.hpp"
#include <max/Compiling/AliasingOptimizations.hpp>
#include <max/Testing/TestSuite.hpp>
#include <iostream>

namespace maxManualTests
{
namespace Compiling
{

	namespace {

		bool unpure( int * write, long * read )
		{
			write = reinterpret_cast< int * >( 5 );

			return read == write;
		}

		MAX_PURE( void pure( int * write, int * read ) )
		{
		}


		static int global = 5;

		bool unpure_with_globals( int * write, int * read )
		{
			write = reinterpret_cast< int * >( 5 );

			return read == write && global == 0;
		}

		MAX_PURE_WITH_GLOBALS( bool pure_with_globals( int * write, int * read ) )
		{
			write = reinterpret_cast< int * >( 5 );

			return read == write && global == 0;
		}

	} // anonymous namespace

/* [MAX_SEMI_PURE](MAX_SEMI_PURE.md)
* [MAX_RESTRICTED_POINTER](MAX_RESTRICTED_POINTER.md)
* [MAX_RESTRICTED_REFERENCE](MAX_RESTRICTED_REFERENCE.md)
* [MAX_RETURNS_RESTRICTED_POINTER](MAX_RETURNS_RESTRICTED_POINTER.md)
*/


	void RunAliasingOptimizationsTestSuite()
	{
		int * Address1 = new int( 5 );
		int * Address2 = new int( 6 );

		char Overlap = 'n';
		std::cin >> Overlap;
		if( Overlap == 'y' )
		{
			delete Address2;
			Address2 = Address1;
		}


		std::cout << unpure( Address1, Address2 );
		//std::cout << pure(   Address1, Address2 );

		//std::cout << unpure_with_globals( Address1, Address2 );
		//std::cout << pure_with_globals(   Address1, Address2 );

		delete Address1;
		if( Overlap != 'y' )
		{
			delete Address2;
		}
	}

} // namespace Compiling
} // namespace maxManualTests