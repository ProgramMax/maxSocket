// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_IP_WINDOWSADDRESSVERSION4POLICY_HPP
#define MAXSOCKET_IP_WINDOWSADDRESSVERSION4POLICY_HPP

#ifdef NO_PRECOMPILED_HEADER
	#include <max/Compiling/ThrowSpecification.hpp>
	#include <string>
	#include <Ws2tcpip.h>
#else
	#include "PrecompiledHeader.hpp"
#endif

namespace maxSocket
{
namespace IP
{

	class WindowsAddressVersion4Policy
	{
	public:

		explicit WindowsAddressVersion4Policy( in_addr Address ) MAX_DOES_NOT_THROW;

		std::string GetRepresentation() MAX_DOES_NOT_THROW;

		in_addr m_Address;

	}; // class WindowsAddressVersion4Policy

} // namespace IP
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_IP_WINDOWSADDRESSVERSION4POLICY_HPP
