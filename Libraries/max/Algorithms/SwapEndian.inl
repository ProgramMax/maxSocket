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

namespace max
{
namespace Algirhtms
{

	inline unsigned int SwapEndian( unsigned int Value )
	{
		return ( ( ( Value & 0xff000000 ) >> 24 ) | ( ( Value & 0x00ff0000 ) >> 8 ) | ( ( Value & 0x0000ff00 ) << 8 )  | ( ( Value & 0x000000ff ) << 24 ) );
	}

	inline unsigned short SwapEndian( unsigned short Value )
	{
		return static_cast< unsigned short >( ( ( Value & 0xff00 ) >> 8 ) | ( ( Value & 0x00ff ) << 8 ) );
	}

	inline int SwapEndian( int Value )
	{
		return SwapEndian( reinterpret_cast< unsigned int >( Value ) );
	}

	inline short SwapEndian( short Value )
	{
		return SwapEndian( reinterpret_cast< unsigned short >( Value ) );
	}

} // namespace Algorithms
} // namespace max
