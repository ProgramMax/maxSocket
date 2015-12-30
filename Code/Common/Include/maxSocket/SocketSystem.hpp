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

#ifndef MAXSOCKET_SOCKETSYSTEM_HPP
#define MAXSOCKET_SOCKETSYSTEM_HPP

#include <max/Compiling/ThrowSpecification.hpp>
#include <maxSocket/AddressFamily.hpp>
#include <vector>
#include <memory>
#include <maxSocket/IP/Address.hpp>
#include <maxSocket/IP/Version.hpp>
#include <maxSocket/Protocol.hpp>
#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxSocket/IP/Addresses.hpp>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{

	namespace CreateSocketSystemResults
	{
		enum Enum
		{
			Success,
			SystemIsNotReady,
			NoSystemSupport,
			LibraryError,
			UnknownError,
		}; // enum Enum
	} // namespace CreateSocketSystemResult

	namespace ResolveHostNameResults
	{
		enum Enum
		{
			Success,
			NameServerReturnedATemporaryFailure,
			NameServerReturnedAPermanentFailure,
			OutOfMemory,
			NetworkHostExistsButHasNoEndPoints,
			UnknownHostName,
			EncounteredAnUnknownAddressFamily,
			SystemError,
			LibraryError,
			AuthoritiveAnswerHostNotFound,
			ExceededMaximumEndPointSanityCheck,
			UnknownError
		}; // enum Enum
	} // namespace ResolveHostNameResults

	namespace CreateSocketAndConnectResults
	{
		enum Enum
		{
			Success,
			UnknownIPVersion,
			UnknownProtocol,
			NoMoreSocketDescriptorsAvailable,
			ConnectionRefused,
			RemoteHostResetConnection,
			TimedOut,
			NetworkUnreachable,
			RemoteAddressInvalid,
			HostUnreachable,
			NetworkDown,
			Interrupted,
			NotAuthorized,
			OutOfMemory,
			LibraryError,
			SystemError,
			UnknownError
		}; // enum Enum
	} // namespace CreateSocketResults

	class Socket;

	class SocketSystem
	{
	public:

		static CreateSocketSystemResults::Enum CreateSocketSystem( std::unique_ptr< SocketSystem > & CreatedSocketSystem ) MAX_DOES_NOT_THROW;

		~SocketSystem() MAX_DOES_NOT_THROW;

		ResolveHostNameResults::Enum ResolveHostName( const char * const HostName,
													  const AddressFamily::Enum AddresFamilyFilter,
													  IP::Addresses & EndPoints
													) MAX_DOES_NOT_THROW;

		CreateSocketAndConnectResults::Enum CreateSocketAndConnect( const IP::Address & EndPoint,
																	const unsigned short Port,
																	const Protocol::Enum Protocol,
																	std::unique_ptr< Socket > & CreatedSocket
																  ) MAX_DOES_NOT_THROW;

	private:

		SocketSystem() MAX_DOES_NOT_THROW = default;

	}; // class SocketSystem

} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_SOCKETSYSTEM_HPP
