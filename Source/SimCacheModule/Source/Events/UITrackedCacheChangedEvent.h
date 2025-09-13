// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UITrackedCacheChangedEvent
	: public Utils::SerialisableEvent
{
public:

	UITrackedCacheChangedEvent( const CacheId& NewCacheId )
		: NewCacheId( NewCacheId )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "id", NewCacheId );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "id", NewCacheId );

		return Success;
	}

public:

	CacheId NewCacheId;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::SerialisableEventTraits< UITrackedCacheChangedEvent >
{
	static constexpr char* Id = "SimCache.UITrackedCacheChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
