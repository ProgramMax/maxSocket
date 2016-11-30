// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PrecompiledHeader.hpp"
#include <maxSocket/SocketSystem.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <maxSocket/IP/Address.hpp>
#include <maxSocket/Socket.hpp>
#include <maxSocket/Protocol.hpp>

int main()
{
	auto SocketSystem = std::unique_ptr< maxSocket::SocketSystem >{};
	auto CreateSocketSystemResult = maxSocket::SocketSystem::CreateSocketSystem( SocketSystem );
	if( CreateSocketSystemResult != maxSocket::CreateSocketSystemResults::Success )
	{
		std::cout << "Error\n";
		return -1;
	}


	auto EndPoints = maxSocket::v0::IP::Addresses{};

	auto ResolveHostNameResults = SocketSystem->ResolveHostName( "google.com", maxSocket::AddressFamily::IPv4, EndPoints );
	if( ResolveHostNameResults != maxSocket::ResolveHostNameResults::Success )
	{
		std::cout << "Error\n";
		return -1;
	}

	if( EndPoints.begin() == EndPoints.end() )
	{
		std::cout << "Error\n";
		return -1;
	}

	{
		// Make a nested scope because the socket should be destroyed before the socket system is

		auto FirstEndPoint = * EndPoints.begin();

		auto Socket = std::unique_ptr< maxSocket::Socket >{};
		auto CreateSocketResult = SocketSystem->CreateSocketAndConnect( FirstEndPoint, 80, maxSocket::Protocol::TCP, Socket );
		if( CreateSocketResult != maxSocket::CreateSocketAndConnectResults::Success )
		{
			std::cout << "Error\n";
			return -1;
		}

		// GET / HTTP/1.1
		// Host: www.google.com
		//
	}

	return 0;
}
