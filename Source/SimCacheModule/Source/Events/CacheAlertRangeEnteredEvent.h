// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class CacheAlertRangeEnteredEvent
	: public Utils::Event
{
public:

	CacheAlertRangeEnteredEvent( const CacheId& Id )
		: Id( Id )
	{}

	CacheId Id;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
