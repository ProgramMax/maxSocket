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

#include "max/Testing/TestSuite.hpp"
#include <iostream>
#include "max/Compiling/UnreferencedValue.hpp"

namespace max
{
namespace Testing
{

	TestSuite::TestSuite( wchar_t const * const Name )
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
		std::wcout << L"Running test suite " << Name << std::endl;
		std::wcout << L"Setting up test suite " << Name << "." << std::endl;
		Setup();
		std::wcout << L"Done setting up test suite " << Name << "." << std::endl;

		for( auto & CurrentTest : Tests )
		{
			std::wcout << L"Running test " << CurrentTest.Name << "." << std::endl;
			CurrentTest.TestFunction( CurrentTest );
			auto TestPassed = CurrentTest.DidTestPass();
			if( TestPassed )
			{
				std::wcout << L"Passed test " << CurrentTest.Name << "." << std::endl;
			} else {
				std::wcout << L"Failed test " << CurrentTest.Name << "." << std::endl;
			}
		}

		std::wcout << L"Tearing down test suite " << Name << "." << std::endl;
		TearDown();
		std::wcout << L"Done tearing down test suite " << Name << "." << std::endl;
	}

	void TestSuite::Setup()
	{
	}

	void TestSuite::TearDown()
	{
	}

} // namespace Testing
} // namespace max
