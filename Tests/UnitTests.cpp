// Copyright 2015, The maxSocket Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// foudn in the LICENSE file.

#include <max/Testing/TestSuite.hpp>

#include <memory>
#include <stdint.h>
#include <maxSocket/Buffer.hpp>

#include <maxSocket/IP/Address.hpp>
#include <maxSocket/IP/Version.hpp>

int main() {

	max::Testing::TestSuite( L"maxSocket::Buffer",
		max::Testing::AddTest( L"constructor",
			[]( auto const & CurrentTestSuite ) {

				const size_t UsedSize = 0;
				const size_t TotalSize = 10;
				auto BufferData = std::make_unique< uint8_t[] >( TotalSize );

				auto TestObject = maxSocket::Buffer{ std::move( BufferData ), UsedSize, TotalSize };

				CurrentTestSuite.AssertEqualTo( TestObject.UsedSize, UsedSize );
				CurrentTestSuite.AssertEqualTo( TestObject.TotalSize, TotalSize );				
			}
		)
	);

	// maxSocket::IP::AddressVersion4
	// maxsocket::IP::AddressVersion6
	// maxSocket::Socket
		// constructor
		// Disconnect
		// Send
		// Receive
	// maxSocket::SocketSystem
		// CreateSocketSystem
		// ResolveHostName
		// CreateSocketAndConnect

	/*
	max::Testing::TestSuite( L"maxSocket:IP::Address",
		max::Testing::AddTest( L"constructor",
			[]( auto const & CurrentTestSuite ) {

				const auto Version = maxSocket::IP::Version::Version4;

				auto TestObject = maxSocket::IP::Address{ Version };

				CurrentTestSuite.AssertEqualTo( TestObject.m_Version, Version );
			}
		)
	);
	*/

}
