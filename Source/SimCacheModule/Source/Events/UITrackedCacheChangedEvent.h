// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/RangeAnnulus.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UITrackedCacheChangedEvent
	: public Utils::Event
{
public:

	UITrackedCacheChangedEvent() = default;

	UITrackedCacheChangedEvent( const std::string& CacheName, const RangeAnnulus Annulus )
		: CacheName( CacheName )
		, Annulus( Annulus )
	{
	}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "name", CacheName );
		Success &= Writer.WriteProperty( "annulus", Annulus );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "name", CacheName );
		Success &= Reader.ReadProperty( "annulus", Annulus );

		return Success;
	}

public:

	std::string CacheName;
	RangeAnnulus Annulus;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::EventTraits< UITrackedCacheChangedEvent >
{
	static constexpr char* Id = "SimCache.UITrackedCacheChangedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
