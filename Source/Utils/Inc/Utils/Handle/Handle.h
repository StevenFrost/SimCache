// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <cstdint>
#include <limits>
#include <utility>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

template< class TId >
class Handle
{
public:

	static_assert( std::is_integral< TId >(), "TId must be an integral type" );

	static Handle Make()
	{
		if ( NextId == std::numeric_limits< TId >::max() )
		{
			return Handle();
		}

		return Handle( NextId++ );
	}

	Handle()
		: Id( InvalidId )
	{}

	explicit Handle( const TId Id )
		: Id( Id )
	{}

	Handle( const Handle& Other ) = default;
	Handle( Handle&& Other ) = default;

	Handle& operator=( const Handle& Other ) = default;
	Handle& operator=( Handle&& Other ) = default;

	bool operator==( const Handle& Other ) const
	{
		return Id == Other.Id;
	}

	bool operator!=( const Handle& Other ) const
	{
		return !( *this == Other );
	}

	TId GetId() const
	{
		return Id;
	}

	bool IsValid() const
	{
		return Id != InvalidId;
	}

	void Reset()
	{
		Id = InvalidId;
	}

private:

	static TId	InvalidId;
	static TId	NextId;

	TId			Id;
};

// -----------------------------------------------------------------------------

template< class TId > TId Handle< TId >::InvalidId = 0;
template< class TId > TId Handle< TId >::NextId = 1;

// -----------------------------------------------------------------------------

struct HandleHasher
{
	template< class TId >
	size_t operator()( const Handle< TId >& Handle ) const
	{
		return std::hash< TId >()( Handle.GetId() );
	}
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
