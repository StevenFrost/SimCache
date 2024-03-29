// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <type_traits>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

template< class TEnum >
bool HasFlag( const TEnum Flags, const TEnum Flag )
{
	static_assert( std::is_enum< TEnum >::value, "TEnum must be an enum type" );

	typedef typename std::underlying_type< TEnum >::type TEnumType;
	return ( static_cast< TEnumType >( Flags ) & static_cast< TEnumType >( Flag ) ) == static_cast< TEnumType >( Flag );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
