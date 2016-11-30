// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP

#define MAX_COMPILER_GCC
#define MAX_COMPILER_VERSION_MAJOR __GNUC__
#define MAX_COMPILER_VERSION_MINOR __GNUC_MINOR__
#if __GNUC__ >= 3
	// __GNUC_PATCHLEVEL__ is new to GCC 3.0
	#define MAX_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#else
	#define MAX_COMPILER_VERSION_PATCH 0
#endif


#if defined(__EXCEPTIONS)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

// noexcept supported in GCC 4.6+
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6) && defined(__GXX_EXPERIMENTAL_CXX0X__)
	#define MAX_NOEXCEPT_SUPPORTED
#endif

// inline namespaces are supported in GCC 4.4+
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4) && defined(__GXX_EXPERIMENTAL_CXX0X__)
	#define MAX_INLINE_NAMESPACES_SUPPORTED
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP