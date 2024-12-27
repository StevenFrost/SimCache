// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class CacheFoundEvent
	: public Utils::SerialisableEvent
{
public:

	CacheFoundEvent() = default;

	CacheFoundEvent( const CacheId& Id )
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
struct Utils::EventTraits< CacheFoundEvent >
{
	static constexpr char* Id = "SimCache.CacheFoundEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
