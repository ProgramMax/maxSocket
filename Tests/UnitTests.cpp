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