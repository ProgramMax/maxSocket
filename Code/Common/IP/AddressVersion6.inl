// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace maxSocket
{
namespace v0
{
namespace IP
{

	template< typename NativeAddressPolicy >
	PlatformIndependentAddressVersion6< NativeAddressPolicy >::PlatformIndependentAddressVersion6( NativeAddressPolicy policy ) MAX_DOES_NOT_THROW
		: v0::IP::Address( v0::IP::Version::Version6 ),
		m_NativeAddressPolicy( policy )
	{
	}

	template< typename NativeAddressPolicy >
	PlatformIndependentAddressVersion6< NativeAddressPolicy >::~PlatformIndependentAddressVersion6() MAX_DOES_NOT_THROW
	{
	}

	template< typename NativeAddressPolicy >
	std::string PlatformIndependentAddressVersion6< NativeAddressPolicy >::GetRepresentation() const MAX_DOES_NOT_THROW
	{
		return m_NativeAddressPolicy.GetRepresentation();
	}

} // namespace IP
} // namespace v0
} // namespace maxSocket
