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
#include "IP/AddressVersion4.hpp"
#include "IP/AddressVersion6.hpp"
#include <maxSocket/Buffer.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace maxSocket
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

} // namespace maxSocket
