// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Geodesy/EarthCoordinate.h>

// -----------------------------------------------------------------------------

class AircraftPositionUpdatedEvent
	: public Utils::Event
{
public:

	// TODO: potentially remove default constructor
	// (currently only required for serialization to work with placeholder NativeEventDispatcher)
	AircraftPositionUpdatedEvent() = default;

	AircraftPositionUpdatedEvent( const Utils::EarthCoordinate& CurrentPosition )
		: CurrentPosition( CurrentPosition )
	{}

public:

	Utils::EarthCoordinate CurrentPosition;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
