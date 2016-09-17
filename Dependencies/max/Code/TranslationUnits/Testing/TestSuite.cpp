// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "max/Testing/TestSuite.hpp"
#include <iostream>
#include "max/Compiling/UnreferencedValue.hpp"

namespace max
{
namespace Testing
{

	TestSuite::TestSuite( char const * const Name )
		: Name( Name )
	{
	}

	void TestSuite::AddTest( max::Testing::Test const & TestToAdd )
	{
		Tests.push_back( TestToAdd );
	}

	void TestSuite::AddTest( max::Testing::Test && TestToAdd )
	{
		Tests.push_back( std::move( TestToAdd ) );
	}

	void TestSuite::RunTests()
	{
		std::cout << "Running test suite " << Name << std::endl;
		std::cout << "Setting up test suite " << Name << "." << std::endl;
		Setup();
		std::cout << "Done setting up test suite " << Name << "." << std::endl;

		for( auto & CurrentTest : Tests )
		{
			std::cout << "Running test " << CurrentTest.Name << "." << std::endl;
			CurrentTest.TestFunction( CurrentTest );
			auto TestPassed = CurrentTest.DidTestPass();
			if( TestPassed )
			{
				std::cout << "Passed test " << CurrentTest.Name << "." << std::endl;
			} else {
				std::cout << "Failed test " << CurrentTest.Name << "." << std::endl;
			}
		}

		std::cout << "Tearing down test suite " << Name << "." << std::endl;
		TearDown();
		std::cout << "Done tearing down test suite " << Name << "." << std::endl;
	}

	void TestSuite::Setup()
	{
	}

	void TestSuite::TearDown()
	{
	}

} // namespace Testing
} // namespace max