// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/RangeAnnulus.h"

#include "Events/RangeAnnulusChangedEvent.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UIRangeAnnulusChangedEvent
	: public Utils::SerialisableEvent
{
public:
	UIRangeAnnulusChangedEvent() = default;

	UIRangeAnnulusChangedEvent( const RangeAnnulusChangedEvent& Event )
		: Annulus( Event.Annulus )
	{
	}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "annulus", Annulus );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "annulus", Annulus );

		return Success;
	}

public:

	RangeAnnulus Annulus;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< UIRangeAnnulusChangedEvent >
{
	static constexpr char* Id = "SimCache.UIRangeAnnulusChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
