// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UICacheSelectedEvent
	: public Utils::SerialisableEvent
{
public:

	UICacheSelectedEvent() = default;

	UICacheSelectedEvent( const CacheId& Id )
		: Id( Id )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "id", Id );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "id", Id );

		return Success;
	}

public:

	CacheId Id;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::SerialisableEventTraits< UICacheSelectedEvent >
{
	static constexpr char* Id = "SimCache.UICacheSelectedEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
