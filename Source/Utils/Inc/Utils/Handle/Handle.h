// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Logging/Log.h>

#include <cstdint>
#include <limits>
#include <utility>

// -----------------------------------------------------------------------------

DECLARE_LOG_CATEGORY( Handle )

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

template< typename T >
struct HandleParams
{
	static_assert( std::is_integral< T >(), "T must be an integral type" );

	static constexpr T InvalidId() { return std::numeric_limits< T >::min(); }
	static constexpr T InitialId() { return std::numeric_limits< T >::min() + 1; }
	static constexpr T MaximumId() { return std::numeric_limits< T >::max(); }
};

// -----------------------------------------------------------------------------

template< class TId, class TParams = HandleParams< TId > >
class Handle
{
public:

	static_assert( std::is_integral< TId >(), "TId must be an integral type" );

	static Handle Make()
	{
		if ( NextId == TParams::MaximumId() )
		{
			LOG( Handle, Error, "Maximum number of valid handles reached." );
			return Handle();
		}

		return Handle( NextId++ );
	}

	Handle()
		: Id( TParams::InvalidId() )
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
		return Id != TParams::InvalidId();
	}

	void Reset()
	{
		Id = TParams::InvalidId();
	}

private:

	static TId	NextId;
	TId			Id;
};

// -----------------------------------------------------------------------------

template< class TId, class TParams >
TId Handle< TId, TParams >::NextId = TParams::InitialId();

// -----------------------------------------------------------------------------

struct HandleHasher
{
	template< class TId, class TParams >
	size_t operator()( const Handle< TId, TParams >& Handle ) const
	{
		return std::hash< TId >()( Handle.GetId() );
	}
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
