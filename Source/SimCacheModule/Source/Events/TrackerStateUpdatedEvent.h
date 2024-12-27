// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"
#include "Core/TrackerState.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class TrackerStateUpdatedEvent
	: public Utils::SerialisableEvent
{
public:
	TrackerStateUpdatedEvent() = default;

	TrackerStateUpdatedEvent( const CacheId& Id, const TrackerState& State )
		: Id( Id )
		, State( State )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "id", Id );
		Success &= Writer.WriteProperty( "state", State );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "id", Id );
		Success &= Reader.ReadProperty( "state", State );

		return Success;
	}

public:

	CacheId Id;
	TrackerState State;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< TrackerStateUpdatedEvent >
{
	static constexpr char* Id = "SimCache.TrackerStateUpdatedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
