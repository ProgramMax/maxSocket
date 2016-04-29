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

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_HPP

// The order of these is important.
// Clang defines both __clang__ and __GNUC__.
// GCC does not define __clang__.
// So the GCC check must come after the Clang check.
// ICC also defines __GNUC__.
// So the check for __ICC must also come before the GCC check.
// Metrowerks and MSVC both define _MSC_VER.
// So check __MWERKS__ prior to checking _MSC_VER.

#if defined __clang__
	// Clang
	#include <max/Compiling/Configuration/Compiler/Clang.hpp>
#elif defined __GNUC__
	// GNU C++
	#include <max/Compiling/Configuration/Compiler/GCC.hpp>
#elif defined _MSC_VER
	// Microsoft Visual C++
	#include <max/Compiling/Configuration/Compiler/VC.hpp>
#else
	#error "Unknown compiler"
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_HPP