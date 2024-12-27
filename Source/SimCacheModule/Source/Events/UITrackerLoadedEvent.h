// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UITrackerLoadedEvent
	: public Utils::Event
{
public:

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final { return true; }
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final { return true; }
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< UITrackerLoadedEvent >
{
	static constexpr char* Id = "SimCache.UITrackerLoadedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
