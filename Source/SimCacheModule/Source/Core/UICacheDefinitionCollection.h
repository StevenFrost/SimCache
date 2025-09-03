// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Optional/Optional.h>

// -----------------------------------------------------------------------------

struct UICacheMetadata
	: public Utils::Serialisation::ISerialisable
{
	UICacheMetadata();
	UICacheMetadata( const CacheMetadata& Metadata, Utils::Optional< Utils::DateTime > DateCollected );

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	CacheId									Id;
	std::vector< CacheAuthorId >			Authors;
	Utils::DateTime							DatePlaced;
	Utils::Optional < Utils::DateTime >		DateCollected;

	uint8_t									Difficulty;
};

// -----------------------------------------------------------------------------

struct UICacheDefinition
	: public Utils::Serialisation::ISerialisable
{
	UICacheDefinition();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	UICacheMetadata				Metadata;
	CacheLocText				LocText;
};

// -----------------------------------------------------------------------------

class UICacheDefinitionCollection
	: public Utils::Serialisation::ISerialisable
{
public:

	UICacheDefinitionCollection();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	std::string							Version;

	std::vector< UICacheDefinition >	CacheDefinitions;
	std::vector< CacheAuthor >			Authors;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
