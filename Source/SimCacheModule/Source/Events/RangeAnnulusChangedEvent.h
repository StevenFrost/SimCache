// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"
#include "Core/RangeAnnulus.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class RangeAnnulusChangedEvent
	: public Utils::Event
{
public:
	RangeAnnulusChangedEvent() = default;

	RangeAnnulusChangedEvent( const CacheId& Id, const RangeAnnulus& Annulus )
		: Id( Id )
		, Annulus( Annulus )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "id", Id );
		Success &= Writer.WriteProperty( "annulus", Annulus );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "id", Id );
		Success &= Reader.ReadProperty( "annulus", Annulus );

		return Success;
	}

public:

	CacheId Id;
	RangeAnnulus Annulus;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< RangeAnnulusChangedEvent >
{
	static constexpr char* Id = "SimCache.RangeAnnulusChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
