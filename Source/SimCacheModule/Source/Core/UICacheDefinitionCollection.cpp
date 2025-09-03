// Copyright (c) 2025 Steven Frost and Orion Lyau

#include "Core/UICacheDefinitionCollection.h"

// -----------------------------------------------------------------------------

UICacheMetadata::UICacheMetadata()
	: Id()
	, Authors()
	, DatePlaced()
	, DateCollected()
	, Difficulty( 1 )
{
}

// -----------------------------------------------------------------------------

UICacheMetadata::UICacheMetadata( const CacheMetadata& Metadata, Utils::Optional<Utils::DateTime> DateCollected )
	: Id( Metadata.Id )
	, Authors( Metadata.Authors )
	, DatePlaced( Metadata.DatePlaced )
	, DateCollected( DateCollected )
	, Difficulty( Metadata.Difficulty )
{
}

// -----------------------------------------------------------------------------

bool UICacheMetadata::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "id", Id );
	Success &= Writer.WriteProperty( "authors", Authors );
	Success &= Writer.WriteProperty( "date_placed", DatePlaced.ToISO8601UTC() );
	// TODO: make writer handle Utils::Optional< T > correctly
	if ( DateCollected.has_value() )
	{
		Success &= Writer.WriteProperty( "date_collected", DateCollected->ToISO8601UTC() );
	}
	else
	{
		Success &= Writer.WriteProperty( "date_collected", false );
	}
	Success &= Writer.WriteProperty( "difficulty", Difficulty );

	return Success;
}

// -----------------------------------------------------------------------------

bool UICacheMetadata::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "id", Id );
	Success &= Reader.ReadProperty( "authors", Authors );

	std::string DatePlacedString;
	Success &= Reader.ReadProperty( "date_placed", DatePlacedString );
	DatePlaced = Utils::DateTime::FromISO8601UTC( DatePlacedString );

	std::string DateCollectedString;
	Success &= Reader.ReadProperty( "date_collected", DateCollectedString );
	DateCollected = Utils::DateTime::FromISO8601UTC( DateCollectedString );

	Success &= Reader.ReadProperty( "difficulty", Difficulty );

	return Success;
}

// -----------------------------------------------------------------------------

UICacheDefinition::UICacheDefinition()
	: Metadata()
	, LocText()
{
}

// -----------------------------------------------------------------------------

bool UICacheDefinition::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "meta", Metadata );
	Success &= Writer.WriteProperty( "loc_text", LocText );

	return Success;
}

// -----------------------------------------------------------------------------

bool UICacheDefinition::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "meta", Metadata );
	Success &= Reader.ReadProperty( "loc_text", LocText );

	return Success;
}

// -----------------------------------------------------------------------------

UICacheDefinitionCollection::UICacheDefinitionCollection()
	: Version()
	, CacheDefinitions()
	, Authors()
{
}

// -----------------------------------------------------------------------------

bool UICacheDefinitionCollection::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "version", Version );
	Success &= Writer.WriteProperty( "cache_definitions", CacheDefinitions );
	Success &= Writer.WriteProperty( "authors", Authors );

	return Success;
}

// -----------------------------------------------------------------------------

bool UICacheDefinitionCollection::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "version", Version );
	Success &= Reader.ReadProperty( "cache_definitions", CacheDefinitions );
	Success &= Reader.ReadProperty( "authors", Authors );

	return Success;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
