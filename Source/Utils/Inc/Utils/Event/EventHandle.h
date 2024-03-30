// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <cstdint>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

class EventHandle
{
public:

	static EventHandle Make();

	EventHandle();

	EventHandle( const EventHandle& Other ) = default;
	EventHandle( EventHandle&& Other ) = default;

	EventHandle& operator=( const EventHandle& Other ) = default;
	EventHandle& operator=( EventHandle&& Other ) = default;

	bool operator==( const EventHandle& Other ) const;
	bool operator!=( const EventHandle& Other ) const;

	bool IsValid() const;

	void Reset();

private:

	EventHandle( const int32_t Id );

	static const int32_t	InvalidId;
	static int32_t			NextId;

	int32_t					Id;

	friend struct EventHandleHasher;
};

// -----------------------------------------------------------------------------

struct EventHandleHasher
{
	size_t operator()( const EventHandle& Handle ) const;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
