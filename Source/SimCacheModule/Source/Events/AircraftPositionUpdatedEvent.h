// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Geodesy/EarthCoordinate.h>

// -----------------------------------------------------------------------------

class AircraftPositionUpdatedEvent
	: public Utils::Event
{
public:

	AircraftPositionUpdatedEvent( const Utils::EarthCoordinate& CurrentPosition )
		: CurrentPosition( CurrentPosition )
	{}

public:

	Utils::EarthCoordinate CurrentPosition;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
