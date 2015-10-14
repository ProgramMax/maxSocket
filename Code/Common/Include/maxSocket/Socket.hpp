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

#ifndef MAXSOCKET_SOCKET_HPP
#define MAXSOCKET_SOCKET_HPP

#ifdef NO_PRECOMPILED_HEADER
//	#include <Winsock2.h>
	#include <sys/socket.h>
	#include <memory>
	#include <max/Compiling/Configuration/Platform.hpp>
#else
	#include "..\..\Windows\PrecompiledHeader.hpp"
#endif // #ifdef NO_PRECOMPILED_HEADER
#include <max/Compiling/ThrowSpecification.hpp>

namespace maxSocket
{
	namespace IP
	{
		class Address;
	} // namespace IP
	class Buffer;

	namespace DisconnectResults
	{
		enum Enum
		{
			Success,
			LibraryError,
			SystemError,
			UnknownError
		}; // enum Enum
	} // namespace DisconnectResults

	namespace SendResults
	{
		enum Enum
		{
			Success,
			ConnectionAborted,
			ConnectionResetByRemoteEndPoint,
			VirtualNetworkReset,
			MessageSizeTooLargeForUnderlyingNetwork
		}; // enum Enum
	} // namespace SendResults

	namespace ReceiveResults
	{
		enum Enum
		{
			Success,
			ConnectionAborted,
			ConnectionResetByRemoteEndPoint,
			ConnectionGracefullyClosedByRemoteEndPoint,
			VirtualNetworkReset,
			TimedOut
		}; // enum Enum
	} // namespace ReceiveResults

	class Socket
	{
	public:

	#if defined(MAX_PLATFORM_WINDOWS)
		explicit Socket( SOCKET NativeSocket ) MAX_DOES_NOT_THROW;
	#endif
	#if defined(MAX_PLATFORM_LINUX)
		explicit Socket( int NativeSocket ) MAX_DOES_NOT_THROW;
	#endif

		~Socket() MAX_DOES_NOT_THROW;

		DisconnectResults::Enum Disconnect() MAX_DOES_NOT_THROW;

		SendResults::Enum Send( Buffer & DataToSend ) MAX_DOES_NOT_THROW;
		ReceiveResults::Enum Receive( Buffer & DataReceived ) MAX_DOES_NOT_THROW;

	private:

	#if defined(MAX_PLATFORM_WINDOWS)
		SOCKET m_Socket;
	#endif
	#if defined(MAX_PLATFORM_LINUX)
		int m_Socket;
	#endif

		friend class SocketSystem;

	};

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_SOCKET_HPP
