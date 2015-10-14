// Copyright 2015, Chris Blume
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Chris Blume nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MAX_CONFIGURATION_PLATFORM_WIN32_HPP
#define MAX_CONFIGURATION_PLATFORM_WIN32_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

#define MAX_PLATFORM_WINDOWS

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
