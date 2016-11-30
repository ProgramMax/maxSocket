// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace max
{
namespace Algirhtms
{

	inline uint32_t SwapEndian( uint32_t Value ) MAX_DOES_NOT_THROW
	{
		return ( ( ( Value & 0xff000000 ) >> 24 ) | ( ( Value & 0x00ff0000 ) >> 8 ) | ( ( Value & 0x0000ff00 ) << 8 )  | ( ( Value & 0x000000ff ) << 24 ) );
	}

	inline uint16_t SwapEndian( uint16_t Value ) MAX_DOES_NOT_THROW
	{
		return static_cast< uint16_t >( ( ( Value & 0xff00 ) >> 8 ) | ( ( Value & 0x00ff ) << 8 ) );
	}

	inline int32_t SwapEndian( int32_t Value ) MAX_DOES_NOT_THROW
	{
		return SwapEndian( static_cast< uint32_t >( Value ) );
	}

	inline int16_t SwapEndian( int16_t Value ) MAX_DOES_NOT_THROW
	{
		return SwapEndian( static_cast< uint16_t >( Value ) );
	}

} // namespace Algorithms
} // namespace max