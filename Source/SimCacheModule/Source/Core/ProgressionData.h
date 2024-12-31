// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Serialisation/Serialisable.h>
#include <Utils/Time/DateTime.h>

#include <vector>

// -----------------------------------------------------------------------------

struct AcquiredCacheMetadata
	: public Utils::Serialisation::ISerialisable
{
public:

	AcquiredCacheMetadata();
	AcquiredCacheMetadata( const CacheId& Id, const Utils::DateTime& TimeAcquired );

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	CacheId			Id;
	Utils::DateTime	TimeAcquired;
};

// -----------------------------------------------------------------------------

struct ProgressionData
	: public Utils::Serialisation::ISerialisable
{
public:

	ProgressionData();

public:

	bool AddAcquiredCacheMetadata( const AcquiredCacheMetadata& CacheMetadata );
	const AcquiredCacheMetadata* GetAcquiredCacheMetadata( const CacheId& Id ) const;

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

private:

	std::vector< AcquiredCacheMetadata >						AcquiredCaches;
	std::unordered_map< CacheId, const AcquiredCacheMetadata* >	CacheIdToMetadataLookup;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
