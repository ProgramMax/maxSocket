// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace max
{
namespace v0
{
namespace Algorithms
{

	// Documentation: ../../../../Documentation/max/v0/Algorithms/IsBetween.md
	template< typename T >
	MAX_PURE_DEFINITION( constexpr inline bool IsBetween( const T Value, const max::Containers::Range< T > & Range ) MAX_DOES_NOT_THROW )
	{
		return Range.Minimum <= Value && Value <= Range.Maximum;
	}

} // namespace Algorithms
} // namespace v0
} // namespace max
