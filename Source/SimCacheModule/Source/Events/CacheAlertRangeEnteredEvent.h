// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class CacheAlertRangeEnteredEvent
	: public Utils::Event
{
public:
	CacheAlertRangeEnteredEvent() = default;

	CacheAlertRangeEnteredEvent( const CacheId& Id )
		: Id( Id )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override
	{

		return Writer.WriteProperty( "id", Id );
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override
	{
		return Reader.ReadProperty( "id", Id );
	}

public:

	CacheId Id;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< CacheAlertRangeEnteredEvent >
{
	static constexpr char* Id = "SimCache.CacheAlertRangeEnteredEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
