// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_BUFFER_HPP
#define MAXSOCKET_BUFFER_HPP

#ifdef NO_PRECOMPILED_HEADER
	#include <memory>
	#include <stdint.h>
#else
	#include "PrecompiledHeader.hpp"
#endif
#include <max/Compiling/ThrowSpecification.hpp>
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{

	class Buffer
	{
	public:

		Buffer( std::unique_ptr< uint8_t[] > && Data, const size_t UsedSize, const size_t TotalSize ) MAX_DOES_NOT_THROW;

		std::unique_ptr< uint8_t[] > Data;
		size_t UsedSize;
		size_t TotalSize;

	}; // class Buffer

} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_BUFFER_HPP
