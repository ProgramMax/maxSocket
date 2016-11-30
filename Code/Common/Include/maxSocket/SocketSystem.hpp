// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXSOCKET_SOCKETSYSTEM_HPP
#define MAXSOCKET_SOCKETSYSTEM_HPP

#include <max/Compiling/Configuration.hpp>

#if defined(MAX_PLATFORM_WINDOWS)
	#pragma comment(lib, "Ws2_32.lib")
#endif

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

	namespace ResolveHostnameResults
	{
		enum Enum
		{
			Success,
			NameServerReturnedATemporaryFailure,
			NameServerReturnedAPermanentFailure,
			OutOfMemory,
			NetworkHostExistsButHasNoEndPoints,
			UnknownHostname,
			SystemError,
			LibraryError,
			UnknownError
		}; // enum Enum
	} // namespace ResolveHostNameResults

	namespace CreateSocketAndConnectResults
	{
		enum Enum
		{
			Success,
			NoMoreSocketDescriptorsAvailable,
			ConnectionRefused,
			ConnectionResetByEndPoint,
			TimedOut,
			NetworkUnreachable,
			EndPointUnreachable,
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

		static CreateSocketSystemResults::Enum CreateSocketSystem(
		                                                           std::unique_ptr< SocketSystem > & CreatedSocketSystem
		                                                         ) MAX_DOES_NOT_THROW;

		~SocketSystem() MAX_DOES_NOT_THROW;

		ResolveHostnameResults::Enum ResolveHostnameUsingOSDefaults(
		                                                             const char * const        Hostname,
													                 const AddressFamily::Enum AddresFamilyFilter,
													                 IP::Addresses &           EndPoints
													               ) MAX_DOES_NOT_THROW;

		CreateSocketAndConnectResults::Enum CreateSocketAndConnect(
		                                                            const IP::Address &         EndPoint,
																	const unsigned short        Port,
																	const Protocol::Enum        Protocol,
																	std::unique_ptr< Socket > & CreatedSocket
																  ) MAX_DOES_NOT_THROW;

	private:

		SocketSystem() MAX_DOES_NOT_THROW = default;

	}; // class SocketSystem

} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )

} // namespace maxSocket

#endif // #ifndef MAXSOCKET_SOCKETSYSTEM_HPP
