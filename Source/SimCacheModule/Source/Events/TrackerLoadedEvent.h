// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class TrackerLoadedEvent
	: public Utils::Event
{
public:

	virtual std::string Serialise() const override final { return {}; }
	virtual void Deserialise( const std::string& Data ) override final {}
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< TrackerLoadedEvent >
{
	static constexpr char* Id = "SimCache.TrackerLoadedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
