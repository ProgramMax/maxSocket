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

// Usage:
// struct T {};
// static_assert( max::Compiling::IsRegular< T >::value, "T should be a regular type." );

#ifndef MAX_COMPILING_ISREGULAR_HPP
#define MAX_COMPILING_ISREGULAR_HPP

namespace max
{
namespace Compiling
{

namespace Detail
{

	template< typename T >
	std::false_type CheckEqualityComparable( T const & t, long );

	template< typename T >
	auto CheckEqualityComparable( T const & t, int )
		-> typename std::is_convertible< decltype( t == t ), bool >::type;

} // namespace Detail

	template< typename T >
	struct IsEqualityComparable
		: decltype( Detail::CheckEqualityComparable( std::declval< T const & >(), 1 ) )
	{};

	template< typename T >
	struct IsRegular
		: std::integral_constant<
			bool,
			std::is_default_constructible< T >::value &&
			std::is_copy_constructible< T >::value &&
			std::is_move_constructible< T >::value &&
			std::is_copy_assignable< T >::value &&
			std::is_move_assignable< T >::value &&
			IsEqualityComparable< T >::value>
	{};

} // namespace Compiling
} // namespace max

#endif // #ifndef MAX_COMPILING_ISREGULAR_HPP
