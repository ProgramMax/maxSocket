// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP
#define MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

// MAX_PURE_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_PURE.md
#if defined( MAX_COMPILER_GCC )
	// this is only available in GCC 2.5 and later
	#if MAX_COMPILER_VERSION_AT_LEAST( 2, 5, 0 )
		#define MAX_PURE_DECLARATION_V0( Declaration ) Declaration __attribute__((const))
		#define MAX_PURE_DEFINITION_V0( Definition ) Definition
	#else
		#define MAX_PURE_DECLARATION_V0( Declaration ) Declaration
		#define MAX_PURE_DEFINITION_V0( Definition ) Definition
	#endif
#elif defined( MAX_COMPILER_VC )
	#define MAX_PURE_DECLARATION_V0( Declaration ) __declspec( noalias ) Declaration
	#define MAX_PURE_DEFINITION_V0( Definition ) __declspec( noalias ) Definition
#else
	#define MAX_PURE_DECLARATION_V0( Declaration ) Declaration
	#define MAX_PURE_DEFINITION_V0( Definition ) Definition
#endif


// MAX_PURE_WITH_GLOBALS_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_PURE_WITH_GLOBALS.md
#if defined( MAX_COMPILER_GCC )
	// this is only available in GCC 2.96 and later
	#if MAX_COMPILER_VERSION_AT_LEAST( 2, 96, 0 )
		#define MAX_PURE_WITH_GLOBALS_V0( Declaration ) Declaration __attribute__((pure))
	#else
		#define MAX_PURE_WITH_GLOBALS_V0( Declaration ) Declaration
	#endif
#elif defined( MAX_COMPILER_VC )
	#define MAX_PURE_WITH_GLOBALS_V0( Declaration ) __declspec( noalias ) Declaration
#else
	#define MAX_PURE_WITH_GLOBALS_V0( Declaration ) Declaration
#endif


// MAX_SEMI_PURE_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_SEMI_PURE.md
#if defined( MAX_COMPILER_VC )
	#define MAX_SEMI_PURE_DECLARATION_V0( Declaration ) __declspec( noalias ) Declaration
	#define MAX_SEMI_PURE_DEFINITION_V0( Definition ) __declspec( noalias ) Definition
#else
	#define MAX_SEMI_PURE_DECLARATION_V0( Declaration ) Declaration
	#define MAX_SEMI_PURE_DEFINITION_V0( Definition ) Definition
#endif


// MAX_RESTRICTED_POINTER_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_RESTRICTED_POINTER.md
#if defined( MAX_COMPILER_GCC )
	#define MAX_RESTRICTED_POINTER_V0 __restrict__
#elif defined(MAX_COMPILER_VC)
	#define MAX_RESTRICTED_POINTER_V0 __restrict
#else
	#define MAX_RESTRICTED_POINTER_V0
#endif


// MAX_RESTRICTED_REFERENCE_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_RESTRICTED_REFERENCE.md
#if defined( MAX_COMPILER_GCC )
	#define MAX_RESTRICTED_REFERENCE_V0 __restrict__
#elif defined( MAX_COMPILER_VC )
	#if MAX_COMPILER_VERSION_AT_LEAST( 14, 0, 0 )
		#define MAX_RESTRICTED_REFERENCE_V0 __restrict
	#else
		#define MAX_RESTRICTED_REFERENCE_V0
	#endif
#else
	#define MAX_RESTRICTED_REFERENCE_V0
#endif


// MAX_RETURNS_RESTRICTED_POINTER_V0
// Documentation: ../../../../Documentation/max/v0/Compiling/MAX_RETURNS_RESTRICTED_POINTER.md
#if defined( MAX_COMPILER_GCC )
	#define MAX_RETURNS_RESTRICTED_POINTER_V0( Declaration ) Declaration __attribute__( malloc )
#elif defined( MAX_COMPILER_VC )
	#define MAX_RETURNS_RESTRICTED_POINTER_V0( Declaration ) __declspec( restrict ) Declaration
#else
	#define MAX_RETURNS_RESTRICTED_POINTER_V0( Declaration ) Declaration
#endif


// API Versioning
#define MAX_PURE_DECLARATION           MAX_PURE_DECLARATION_V0
#define MAX_PURE_DEFINITION            MAX_PURE_DEFINITION_V0

#define MAX_PURE_WITH_GLOBALS          MAX_PURE_WITH_GLOBALS_V0

#define MAX_SEMI_PURE_DECLARATION      MAX_SEMI_PURE_DECLARATION_V0
#define MAX_SEMI_PURE_DEFINITION       MAX_SEMI_PURE_DEFINITION_V0
#define MAX_RESTRICTED_POINTER         MAX_RESTRICTED_POINTER_V0
#define MAX_RESTRICTED_REFERENCE       MAX_RESTRICTED_REFERENCE_V0
#define MAX_RETURNS_RESTRICTED_POINTER MAX_RETURNS_RESTRICTED_POINTER_V0

#endif // #ifndef MAX_COMPILING_FUNCTIONOPTIMIZATIONS_HPP
