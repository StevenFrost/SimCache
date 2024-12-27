// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Serialisation/Serialisable.h>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

struct Event
{
	Event() = default;
	virtual ~Event() = default;
};

// -----------------------------------------------------------------------------

struct SerialisableEvent
	: public Event
	, public Serialisation::ISerialisable
{
	SerialisableEvent() = default;
	virtual ~SerialisableEvent() = default;
};

// -----------------------------------------------------------------------------

template< class TEvent >
struct EventTraits
{
	static_assert( std::is_base_of< Event, TEvent >::value, "TEvent must be derived from Event" );
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
