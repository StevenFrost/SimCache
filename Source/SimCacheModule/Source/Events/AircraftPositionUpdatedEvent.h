// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Geodesy/EarthCoordinate.h>
#include <Utils/Optional/Optional.h>

// -----------------------------------------------------------------------------

class AircraftPositionUpdatedEvent
	: public Utils::Event
{
public:

	AircraftPositionUpdatedEvent( const Utils::Optional< Utils::EarthCoordinate >& PreviousPosition, const Utils::EarthCoordinate& CurrentPosition )
		: PreviousPosition( PreviousPosition )
		, CurrentPosition( CurrentPosition )
	{}

public:

	Utils::Optional< Utils::EarthCoordinate >	PreviousPosition;
	Utils::EarthCoordinate						CurrentPosition;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
