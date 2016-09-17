// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <max/Hardware/CPU/MakeCPUID.hpp>
#include <max/Hardware/CPU/CPUIDPolicies/VCIntrinsicCPUIDPolicy.hpp>
#include <max/Hardware/CPU/IsCPUIDAvailablePolicies/AssemblyIsCPUIDAvailablePolicy.hpp>
#include <max/Hardware/CPU/CPUIDSubleafArgumentsAndResult.hpp>

#include <vector>

namespace max
{
namespace CPU
{

	namespace
	{
		template< typename CPUIDPolicy >
		std::vector< max::CPU::CPUIDSubleafArgumentsAndResult > GetCPUIDSubleafResults() noexcept;
	} // Anonymous namespace


	CPUID MakeCPUID() noexcept
	{
		typedef VCIntrinsicCPUIDPolicy            CPUIDPolicy;
		typedef AssemblyIsCPUIDAvailablePolicy IsCPUIDAvailablePolicy;


		if( ! IsCPUIDAvailablePolicy::IsCPUIDAvailable() )
		{
			return CPUID{ std::vector< CPUIDSubleafArgumentsAndResult >{} };
		}

		return CPUID{ GetCPUIDSubleafResults< CPUIDPolicy >() };
	}


	namespace
	{

		template< typename CPUIDPolicy >
		std::vector< max::CPU::CPUIDSubleafArgumentsAndResult > GetCPUIDSubleafResults() noexcept
		{
			std::vector< max::CPU::CPUIDSubleafArgumentsAndResult > SubleafResults;



			// cpuid function 0 returns the highest valid function number in EAX
			max::CPU::CPUIDSubleafResult Result = {};
			CPUIDPolicy::CPUID( Result, 0 );
			const auto LeafCount = Result.EAX;


			// Populate CPUID results
			// We already ran function 0.
			SubleafResults.emplace_back( 0, 0, std::move( Result ) );
			// So we will loop through 1-x
			for( uint32_t Leaf = 1; Leaf <= LeafCount; Leaf++ )
			{
				if( Leaf == 4 ) //-V112 Dangerous magic number 4 used -- in this case, it isn't a sizeof(int)
				{
					for( uint32_t Subleaf = 0; ; Subleaf++ )
					{
						CPUIDPolicy::CPUIDExtended( Result, Leaf, Subleaf );
						if( Result.EAX == 0 && Result.EBX == 0 && Result.ECX == 0 && Result.EDX == 0 )
						{
							break;
						}

						SubleafResults.emplace_back( Leaf, Subleaf, std::move( Result ) );
					}
				} else {
					CPUIDPolicy::CPUID( Result, Leaf );
					SubleafResults.emplace_back( Leaf, 0, std::move( Result ) );
				}
			}



			// cpuid function 0x8000'0000 returns the highest valid extended function number in EAX
			CPUIDPolicy::CPUID( Result, 0x8000'0000 ); // -V112 Dangerous magic number 0x8000'0000 -- in this case
			const auto ExtendedLeafCount = Result.EAX - 0x8000'0000; // -V112


			// Populate CPUID results
			// We already ran extended function 0.
			SubleafResults.emplace_back( 0x8000'0000, 0, std::move( Result ) ); // -V112
			// So we will loop through 1-x
			for( uint32_t i = 1; i <= ExtendedLeafCount; i++ )
			{
				CPUIDPolicy::CPUID( Result, i + 0x8000'0000 ); // -V112
				SubleafResults.emplace_back( i + 0x8000'0000, 0, std::move( Result ) ); // -V112
			}


			return SubleafResults;
		}

	} // Anonymous namespace

} // namespace CPU
} // namespace max
