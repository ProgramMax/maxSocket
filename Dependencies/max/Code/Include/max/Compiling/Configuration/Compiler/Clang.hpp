// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP

#define MAX_COMPILER_CLANG
#define MAX_COMPILER_VERSION_MAJOR __clang_major__
#define MAX_COMPILER_VERSION_MINOR __clang_minor__
#define MAX_COMPILER_VERSION_PATCH __clang_patchlevel__

#if __has_feature(cxx_exceptions)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

#if __has_feature(cxx_noexcept)
	#define MAX_NOEXCEPT_SUPPORTED
#endif

#if __has_feature(cxx_inline_namespaces)
	#define MAX_INLINE_NAMESPACES_SUPPORTED
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP