// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include "Core/UICacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UICacheListChangedEvent
	: public Utils::SerialisableEvent
{
public:

	UICacheListChangedEvent( const UICacheDefinitionCollection& Caches )
		: Caches( Caches )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override
	{
		return Caches.Serialise( Writer );
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override
	{
		return Caches.Deserialise( Reader );
	}

public:

	UICacheDefinitionCollection Caches;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::SerialisableEventTraits< UICacheListChangedEvent >
{
	static constexpr char* Id = "SimCache.UICacheListChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
