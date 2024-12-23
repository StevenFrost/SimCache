// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Geodesy/EarthCoordinate.h>

// -----------------------------------------------------------------------------

class AircraftPositionUpdatedEvent
	: public Utils::Event
{
public:

	AircraftPositionUpdatedEvent() = default;

	AircraftPositionUpdatedEvent( const Utils::EarthCoordinate& CurrentPosition )
		: CurrentPosition( CurrentPosition )
	{}

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		return Writer.WriteProperty( "CurrentPosition", CurrentPosition );
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		return Reader.ReadProperty( "CurrentPosition", CurrentPosition );
	}

public:

	Utils::EarthCoordinate CurrentPosition;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< AircraftPositionUpdatedEvent >
{
	static constexpr char* Id = "SimCache.AircraftPositionUpdatedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
