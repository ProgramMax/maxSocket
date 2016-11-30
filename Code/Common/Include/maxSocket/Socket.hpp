// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
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

} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket

#endif // #ifndef MAXSOCKET_SOCKET_HPP
