// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "RangeTest.hpp"
#include "IsBetweenTest.hpp"

int main()
{

	maxAutomatedTests::Containers::RunRangeTestSuite();
	maxAutomatedTests::Algorithms::RunIsBetweenTestSuite();

	return 0;
}