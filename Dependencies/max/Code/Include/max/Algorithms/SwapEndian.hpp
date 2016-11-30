// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_ALGORITHMS_SWAPENDIAN_HPP
#define MAX_ALGORITHMS_SWAPENDIAN_HPP

#include <max/Compiling/FunctionOptimizations.hpp>
#include <cstdint>
#include <max/Compiling/ThrowSpecification.hpp>

namespace max
{
namespace Algorithms
{

	Pure( inline uint32_t SwapEndian( uint32_t Value ) MAX_DOES_NOT_THROW );
	Pure( inline uint16_t SwapEndian( uint16_t Value ) MAX_DOES_NOT_THROW );
	Pure( inline int32_t  SwapEndian( int32_t  Value ) MAX_DOES_NOT_THROW );
	Pure( inline int16_t  SwapEndian( int16_t  Value ) MAX_DOES_NOT_THROW );

} // namespace Algorithms
} // namespace max

#include <max/Algorithms/SwapEndian.inl>

#endif // #ifndef MAX_ALGORITHMS_SWAPENDIAN_HPP