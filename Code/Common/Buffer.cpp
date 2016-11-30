// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include <maxSocket/Buffer.hpp>
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
namespace v0
{

	Buffer::Buffer( std::unique_ptr< uint8_t[] > && Data, const size_t UsedSize, const size_t TotalSize ) MAX_DOES_NOT_THROW
		: Data(      std::move( Data ) )
		, UsedSize(  UsedSize )
		, TotalSize( TotalSize )
	{
	}

} // namespace v0
} // namespace maxSocket
