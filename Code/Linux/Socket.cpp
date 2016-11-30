// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxSocket/Socket.hpp>
#include <maxSocket/IP/Address.hpp>
#include "IP/AddressVersion4.hpp"
#include "IP/AddressVersion6.hpp"
#include <maxSocket/Buffer.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace maxSocket
{
namespace v0
{

	Socket::~Socket() MAX_DOES_NOT_THROW
	{
		close( m_Socket );
		// even if there is an error, ignore it...we're in a destructor
	}

	DisconnectResults::Enum Socket::Disconnect() MAX_DOES_NOT_THROW
	{
		auto CloseResult = close( m_Socket );
		if( CloseResult == -1 )
		{
			auto ErrorCode = errno;
			switch( ErrorCode )
			{
			case EBADF: // The filedes argument is not an open file descriptor.
				return DisconnectResults::LibraryError;
			case EINTR: // The close() function was interrupted by a signal.
			case EIO:   // An I/O error occurred while reading from or writing to the file system.
				return DisconnectResults::SystemError;
			default:
				return DisconnectResults::UnknownError;
			}
		}

		return DisconnectResults::Success;
	}

	SendResults::Enum Socket::Send( Buffer & DataToSend ) MAX_DOES_NOT_THROW
	{
		auto Returning = SendResults::Success;

		send( m_Socket, DataToSend.Data.get(), DataToSend.UsedSize, 0 );

		DataToSend.UsedSize = 0;

		return Returning;
	}

	ReceiveResults::Enum Socket::Receive( Buffer & DataReceived ) MAX_DOES_NOT_THROW
	{
		auto Returning = ReceiveResults::Success;

		auto BytesReceived = recv( m_Socket, DataReceived.Data.get(), DataReceived.TotalSize, 0 );
		DataReceived.UsedSize = BytesReceived;

		return Returning;
	}

	Socket::Socket( int NativeSocket ) MAX_DOES_NOT_THROW
		: m_Socket( NativeSocket )
	{
	}

} // namespace v0
} // namespace maxSocket
