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
#include <max/Compiling/CurrentVersionNamespace.hpp>
#include "AddressesIterator.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace maxSocket
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace IP
{

	class Addresses
	{
	public:

		Addresses() MAX_DOES_NOT_THROW;
		Addresses( const Addresses & rhs ) MAX_DOES_NOT_THROW = delete;
		Addresses( Addresses && rhs ) MAX_DOES_NOT_THROW;
		explicit Addresses( addrinfo * LinuxEndPoints ) MAX_DOES_NOT_THROW;

		~Addresses() MAX_DOES_NOT_THROW;

		Addresses & operator =( const Addresses & rhs ) MAX_DOES_NOT_THROW = delete;
		Addresses & operator =( Addresses && rhs ) MAX_DOES_NOT_THROW;

		AddressesIterator begin() const MAX_DOES_NOT_THROW;
		AddressesIterator end() const MAX_DOES_NOT_THROW;

	private:

		addrinfo * LinuxEndPoints;

	};

} // namespace IP
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxSocket
