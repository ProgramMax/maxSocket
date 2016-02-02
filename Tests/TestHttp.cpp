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
