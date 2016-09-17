// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_CONFIGURATION_PLATFORM_WIN32_HPP
#define MAX_CONFIGURATION_PLATFORM_WIN32_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

#define MAX_PLATFORM_WINDOWS

#ifdef _WIN32
	#define MAX_32BIT_WORD_SIZE
#endif

#ifdef _WIN64
	#define MAX_64BIT_WORD_SIZE
#endif

#ifdef MAX_COMPILER_GCC
	#ifdef __x86_64
		#define MAX_X86_64
	#endif
	#ifdef __i386__
		#define MAX_X86
	#endif
	#ifdef __IA64__
		#define MAX_IA64
	#endif
#endif // #ifdef MAX_COMPILER_GCC

#ifdef MAX_COMPILER_VC
	#ifdef _M_X64
		#define MAX_X86_64
	#endif
	#ifdef _M_IX86
		#define MAX_X86
	#endif
	#ifdef _M_IA64
		#define MAX_IA64
	#endif
#endif // #ifdef MAX_COMPILER_VC

#endif // #ifndef MAX_CONFIGURATION_PLATFORM_WIN32_HPP