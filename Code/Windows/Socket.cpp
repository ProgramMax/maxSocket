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

#include "PrecompiledHeader.hpp"
#include <maxSocket/Socket.hpp>
#include <maxSocket/IP/Address.hpp>
#include "..\Common\IP\AddressVersion4.hpp"
#include "..\Common\IP\AddressVersion6.hpp"
#include <maxSocket/Buffer.hpp>
#include <max/Compiling/CurrentVersionNamespace.hpp>

namespace maxSocket
{
namespace v0
{

	Socket::Socket( SOCKET NativeSocket ) MAX_DOES_NOT_THROW
	: m_Socket( NativeSocket )
	{
	}

	Socket::~Socket() MAX_DOES_NOT_THROW
	{
		closesocket( m_Socket );
		// even if there is an error, ignore it...we're in a destructor
	}

	DisconnectResults::Enum Socket::Disconnect() MAX_DOES_NOT_THROW
	{
		/*
		Note: Closing the socket doesn't nessisarily guarantee that pending I/O is cancelled.
		So don't clean up all resources (like WSAOVERLAPPED structures) until the I/O is indeed completed.
		*/
		auto CloseResult = closesocket( m_Socket );
		if( CloseResult == SOCKET_ERROR )
		{
			auto ErrorCode = WSAGetLastError();
			switch( ErrorCode )
			{
			case WSANOTINITIALISED:
			case WSAENETDOWN:
			case WSAENOTSOCK:
			case WSAEINPROGRESS:
			case WSAEINTR:
			case WSAEWOULDBLOCK:
				return DisconnectResults::LibraryError;

			default:
				return DisconnectResults::UnknownError;
			}
		}

		return DisconnectResults::Success;
	}

	SendResults::Enum Socket::Send( Buffer & DataToSend ) MAX_DOES_NOT_THROW
	{
		auto Returning = SendResults::Success;


		auto WinsockBuffer = WSABUF{};
		WinsockBuffer.buf  = reinterpret_cast< CHAR * >( DataToSend.Data.get() );
		// TODO: Handle size conversion here
		/*
		if( DataToSend.UsedSize > static_cast< size_t >( std::numeric_limits< decltype( WinsockBuffer.len ) >::max() ) )
		{
			// handle the error
		}
		*/
		WinsockBuffer.len  = static_cast< decltype( WinsockBuffer.len ) >( DataToSend.UsedSize );

		// max buffer size found by getting the value of socket option SO_MAX_MSG_SIZE

		auto BytesSent = DWORD{};
		auto SendResult = WSASend( m_Socket, & WinsockBuffer, 1, & BytesSent, 0, NULL /* Overlapped struction */, NULL /* Completion routine */ );
		if( SendResult == SOCKET_ERROR )
		{
			auto ErrorCode = WSAGetLastError();
			switch( ErrorCode )
			{
			case WSAEFAULT:
			case WSAEINTR:
			case WSAEINPROGRESS:
			case WSAEINVAL:
			case WSAENETDOWN:
			case WSAENOBUFS:
			case WSAENOTCONN:
			case WSAENOTSOCK:
			case WSAEOPNOTSUPP:
			case WSANOTINITIALISED:
			case WSA_OPERATION_ABORTED:
			case WSAESHUTDOWN:   // The socket has been shut down; it is not possible to WSASend on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH.
			case WSAEWOULDBLOCK: // Overlapped sockets: There are too many outstanding overlapped I/O requests.
								 // Nonoverlapped sockets: The socket is marked as nonblocking and the send operation cannot be completed immediately.
				//throw Exceptions::ShouldNotHappen();
				break;

			case WSA_IO_PENDING: // overlapped operation initiated (but not yet completed) - this is fine and normal, not an error
				break;

			case WSAECONNABORTED: // The virtual circuit was terminated due to a time-out or other failure.
								  // not nessisarily an error - should probably handle this as an accepted case
				Returning = SendResults::ConnectionAborted;
				break;
			case WSAECONNRESET: // For a stream socket, the virtual circuit was reset by the remote side.
								// The application should close the socket as it is no longer usable.
								// For a UDP datagram socket, this error would indicate that a previous send operation resulted in an ICMP "Port Unreachable" message.
				Returning = SendResults::ConnectionResetByRemoteEndPoint;
				break;
			case WSAENETRESET: // For a stream socket, the connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.
							   // For a datagram socket, this error indicates that the time to live has expired.
				Returning = SendResults::VirtualNetworkReset;
				break;
			case WSAEMSGSIZE: // The socket is message oriented, and the message is larger than the maximum supported by the underlying transport.
				Returning = SendResults::MessageSizeTooLargeForUnderlyingNetwork;
				break;

			default:
				//throw Exceptions::UnknownError();
				break;
			}
		}


		DataToSend.UsedSize = 0;

		return Returning;
	}

	ReceiveResults::Enum Socket::Receive( Buffer & DataReceived ) MAX_DOES_NOT_THROW
	{
		auto Returning = ReceiveResults::Success;


		auto WinsockBuffer = WSABUF{};
		WinsockBuffer.buf  = reinterpret_cast< CHAR * >( DataReceived.Data.get() );
		// TODO: Handle size conversion here
		/*
		if( DataToSend.UsedSize > static_cast< size_t >( std::numeric_limits< decltype( WinsockBuffer.len ) >::max() ) )
		{
			// handle the error
		}
		*/
		WinsockBuffer.len  = static_cast< decltype( WinsockBuffer.len ) >( DataReceived.TotalSize );

		auto BytesReceived = DWORD{};
		auto ReceiveResult = WSARecv( m_Socket, & WinsockBuffer, 1, & BytesReceived, 0, NULL /* overlapped structure */, NULL /* completion routine */ );
		if( ReceiveResult == SOCKET_ERROR )
		{
			auto ErrorCode = WSAGetLastError();
			switch( ErrorCode )
			{
			case WSA_IO_PENDING: // not an error - it means the overlapped procedure is scheduled
				break;

			case WSAEFAULT:
			case WSAEINPROGRESS:
			case WSAEINTR:
			case WSAEINVAL:
			case WSAEMSGSIZE:
			case WSAENETDOWN:
			case WSAENOTSOCK:
			case WSAEOPNOTSUPP:
			case WSANOTINITIALISED:
			case WSAENOTCONN:           // The socket is not connected.
			case WSAESHUTDOWN:          // The socket has been shut down; it is not possible to call WSARecv on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.
			case WSAEWOULDBLOCK:        // Overlapped sockets: there are too many outstanding overlapped I/O requests.
										// Nonoverlapped sockets: The socket is marked as nonblocking and the receive operation cannot be completed immediately.
			case WSA_OPERATION_ABORTED: // The overlapped operation has been canceled due to the closure of the socket.
				//throw Exceptions::ShouldNotHappen();
				break;

			case WSAECONNABORTED:
				Returning = ReceiveResults::ConnectionAborted;
				break;
			case WSAECONNRESET: // For a stream socket, the virtual circuit was reset by the remote side.
								// The application should close the socket as it is no longer usable.
								// For a UDP datagram socket, this error would indicate that a previous send operation resulted in an ICMP "Port Unreachable" message.
				Returning = ReceiveResults::ConnectionResetByRemoteEndPoint;
				break;
			case WSAEDISCON: // Socket s is message oriented and the virtual circuit was gracefully closed by the remote side.
				Returning = ReceiveResults::ConnectionGracefullyClosedByRemoteEndPoint;
				break;
			case WSAENETRESET: // For a connection-oriented socket, this error indicates that the connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.
							   // For a datagram socket, this error indicates that the time to live has expired.
				Returning = ReceiveResults::VirtualNetworkReset;
				break;
			case WSAETIMEDOUT: // The connection has been dropped because of a network failure or because the peer system failed to respond.
				Returning = ReceiveResults::TimedOut;
				break;

			default:
				//throw Exceptions::UnknownError();
				break;
			}
		}

		if( BytesReceived == 0 )
		{
			// graceful shutdown
		}

		DataReceived.UsedSize = BytesReceived;

		return Returning;
	}

} // namespace v0
} // namespace maxSocket