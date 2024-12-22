// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class TrackedCacheChangedEvent
	: public Utils::Event
{
public:

	TrackedCacheChangedEvent() = default;
	TrackedCacheChangedEvent( const CacheId NewCacheId )
		: NewCacheId( NewCacheId )
	{}

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		return Writer.WriteProperty( "NewCacheId", NewCacheId );
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		return Reader.ReadProperty( "NewCacheId", NewCacheId );
	}

	CacheId NewCacheId;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< TrackedCacheChangedEvent >
{
	static constexpr char* Id = "SimCache.TrackedCacheChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
