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

	RangeAnnulusChangedEvent( const CacheId& Id, const RangeAnnulus& Annulus )
		: Id( Id )
		, Annulus( Annulus )
	{}

	CacheId Id;
	RangeAnnulus Annulus;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
