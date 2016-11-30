// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxSocket/SocketSystem.hpp>
#include <iostream>
#include <memory>
#include <maxSocket/IP/Address.hpp>

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

	auto ResolveHostNameResult = SocketSystem->ResolveHostnameUsingOSDefaults( "google.com", maxSocket::AddressFamily::Any, EndPoints );
	if( ResolveHostNameResult != maxSocket::ResolveHostnameResults::Success )
	{
		std::cout << "Error\n";
		return -1;
	}

	for( const auto & EndPoint : EndPoints )
	{
		std::cout << "EndPoint: " << EndPoint.GetRepresentation() << "\n";
	}

	return 0;
}
