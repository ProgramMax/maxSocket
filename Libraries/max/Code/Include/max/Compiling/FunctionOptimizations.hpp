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

#ifndef MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP
#define MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

//
// A semi-pure function is one that references or modifies
// only locals, arguments, and first-level indirections of arguments.
// This means param1->foo; is okay.
// But param1->member1->foo isn't okay. This is a second-level indirection.
//
// Usage:
// MAX_SEMI_PURE( void foo() );
//
// template< typename T >
// MAX_SEMI_PURE( inline T Max( const T & lhs, const T & rhs ) );
//

#ifdef MAX_COMPILER_VC
	#define MAX_SEMI_PURE( Declaration ) __declspec( noalias ) Declaration
#else
	#define MAX_SEMI_PURE( Declaration ) Declaration
#endif



//
// A pure function is like a semi-pure except if cannot follow a first-level indirection.
// This means no pointers or references.
//
// Usage:
// MAX_PURE( void foo() );
//
// template< typename T >
// MAX_PURE( inline T Max( const T lhs, const T rhs ) );
//

#ifdef MAX_COMPILER_GCC
	// this is only available in GCC 2.5 and later
	#if COMPILER_VERSION_MAJOR > 2 || ( COMPILER_VERSION_MAJOR == 2 && COMPILER_VERSION_MINOR >= 5 )
		#define MAX_PURE( Declaration ) Declaration __attribute__((const))
	#else
		#define MAX_PURE( Declaration ) Declaration
	#endif
#else
	#ifdef MAX_COMPILER_VC
		#define MAX_PURE( Declaration ) __declspec( noalias ) ( Declaration )
	#else
		#define MAX_PURE( Declaration ) Declaration
	#endif
#else
	#define MAX_PURE( Declaration ) Declaration
#endif

//
// A unique pointer is a parameter that cannot be aliased.
// This means the object being pointed to cannot be pointed to by any other pointer.
//
// Usage:
// void free( MAX_UNIQUE_POINTER void * ptr );
//

#ifdef MAX_COMPILER_VC
	#define MAX_UNIQUE_POINTER __restrict
#else
	#define MAX_UNIQUE_POINTER
#endif

//
// Used when a function returns a pointer that has no other aliases.
// This means no other pointer will point to this same location.
// This makes sense for malloc:
//
// MAX_RETURNS_UNIQUE_POINTER void * malloc( size_t size );
//

#ifdef MAX_COMPILER_VC
	#define MAX_RETURNS_UNIQUE_POINTER __declspec( restrict )
#else
	#define MAX_RETURNS_UNIQUE_POINTER
#endif

#endif // #ifndef MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP