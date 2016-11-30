// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_PRECOMPILEDHEADER_HPP
#define MAXSOCKET_PRECOMPILEDHEADER_HPP

#ifndef NO_PRECOMPILED_HEADER
	#pragma message("Compiling precompiled header - this should only happen once per project build")

	#define NOMINMAX

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

	#include <Windows.h>

	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <Winsock2.h>
	#include <Ws2tcpip.h>

	#pragma comment(lib, "Ws2_32.lib")

	#include <list>

	#include <memory>

	#include <max/Compiling/ThrowSpecification.hpp>
#endif // #ifndef NO_PRECOMPILED_HEADER

#endif // #ifndef MAXSOCKET_PRECOMPILEDHEADER_HPP
