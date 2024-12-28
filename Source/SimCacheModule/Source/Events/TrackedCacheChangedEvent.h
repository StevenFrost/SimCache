// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class TrackedCacheChangedEvent
	: public Utils::Event
{
public:

	TrackedCacheChangedEvent( const CacheId NewCacheId )
		: NewCacheId( NewCacheId )
	{}

	CacheId NewCacheId;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
