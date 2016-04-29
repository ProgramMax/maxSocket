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

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP

#define MAX_COMPILER_CLANG
#define MAX_COMPILER_VERSION_MAJOR    __clang_major__
#define MAX_COMPILER_VERSION_MINOR    __clang_minor__
#define MAX_COMPILER_VERSION_REVISION __clang_patchlevel__

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