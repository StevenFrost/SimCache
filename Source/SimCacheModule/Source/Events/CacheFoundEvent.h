// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class CacheFoundEvent
	: public Utils::Event
{
public:

	CacheFoundEvent( const CacheId& Id )
		: Id( Id )
	{}

	CacheId Id;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
