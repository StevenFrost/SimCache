// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <type_traits>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

template< class TEnum >
bool HasFlag( const TEnum Value, const TEnum FlagToCheck )
{
	static_assert( std::is_enum< TEnum >::value, "TEnum must be an enum type" );

	typedef typename std::underlying_type< TEnum >::type TEnumType;
	return ( static_cast< TEnumType >( Value ) & static_cast< TEnumType >( FlagToCheck ) ) == static_cast< TEnumType >( FlagToCheck );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
