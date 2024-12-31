// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Core/ProgressionData.h"

// -----------------------------------------------------------------------------

AcquiredCacheMetadata::AcquiredCacheMetadata()
	: Id()
	, TimeAcquired()
{
}

// -----------------------------------------------------------------------------

AcquiredCacheMetadata::AcquiredCacheMetadata( const CacheId& Id, const Utils::DateTime& TimeAcquired )
	: Id( Id )
	, TimeAcquired( TimeAcquired )
{
}

// -----------------------------------------------------------------------------

bool AcquiredCacheMetadata::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "id", Id );
	Success &= Writer.WriteProperty( "time_acquired", TimeAcquired.ToISO8601UTC() );

	return Success;
}

// -----------------------------------------------------------------------------

bool AcquiredCacheMetadata::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "id", Id );

	std::string TimeAcquiredString;
	Success &= Reader.ReadProperty( "time_acquired", TimeAcquiredString );
	TimeAcquired = Utils::DateTime::FromISO8601UTC( TimeAcquiredString );

	return Success;
}

// -----------------------------------------------------------------------------

ProgressionData::ProgressionData()
	: AcquiredCaches()
	, CacheIdToMetadataLookup()
{
}

// -----------------------------------------------------------------------------

bool ProgressionData::AddAcquiredCacheMetadata( const AcquiredCacheMetadata& CacheMetadata )
{
	if ( !GetAcquiredCacheMetadata( CacheMetadata.Id ) )
	{
		AcquiredCaches.push_back( CacheMetadata );
		CacheIdToMetadataLookup[ CacheMetadata.Id ] = &AcquiredCaches.back();
		return true;
	}
	return false;
}

// -----------------------------------------------------------------------------

const AcquiredCacheMetadata* ProgressionData::GetAcquiredCacheMetadata( const CacheId& Id ) const
{
	auto Iterator = CacheIdToMetadataLookup.find( Id );
	if ( Iterator != CacheIdToMetadataLookup.end() )
	{
		return Iterator->second;
	}
	return nullptr;
}

// -----------------------------------------------------------------------------

bool ProgressionData::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "acquired_caches", AcquiredCaches );

	return Success;
}

// -----------------------------------------------------------------------------

bool ProgressionData::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "acquired_caches", AcquiredCaches );

	for ( auto& CacheMetadata : AcquiredCaches )
	{
		CacheIdToMetadataLookup[ CacheMetadata.Id ] = &CacheMetadata;
	}

	return Success;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
