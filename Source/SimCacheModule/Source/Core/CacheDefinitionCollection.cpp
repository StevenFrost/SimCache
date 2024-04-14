// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Core/CacheDefinitionCollection.h"

// -----------------------------------------------------------------------------

CacheMetadata::CacheMetadata()
	: Id()
	, Authors()
	, DatePlaced()
	, Difficulty( 1 )
	, SimObjectTitle( "SimCache" )
{
}

// -----------------------------------------------------------------------------

bool CacheMetadata::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "id", Id );
	Success &= Writer.WriteProperty( "authors", Authors );
	Success &= Writer.WriteProperty( "date_placed", DatePlaced.ToISO8601UTC() );
	Success &= Writer.WriteProperty( "difficulty", Difficulty );
	Success &= Writer.WriteProperty( "simobject_title", SimObjectTitle );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheMetadata::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "id", Id );
	Success &= Reader.ReadProperty( "authors", Authors );

	std::string DatePlacedString;
	Success &= Reader.ReadProperty( "date_placed", DatePlacedString );
	DatePlaced = Utils::DateTime::FromISO8601UTC( DatePlacedString );

	Success &= Reader.ReadProperty( "difficulty", Difficulty );
	Success &= Reader.ReadProperty( "simobject_title", SimObjectTitle );

	return Success;
}

// -----------------------------------------------------------------------------

CacheText::CacheText()
	: Title()
	, Description()
	, Hint()
{
}

// -----------------------------------------------------------------------------

bool CacheText::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "title", Title );
	Success &= Writer.WriteProperty( "description", Description );
	Success &= Writer.WriteProperty( "hint", Hint );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheText::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "title", Title );
	Success &= Reader.ReadProperty( "description", Description );
	Success &= Reader.ReadProperty( "hint", Hint );

	return Success;
}

// -----------------------------------------------------------------------------

CacheLocText::CacheLocText()
	: Locale()
	, Text()
{
}

// -----------------------------------------------------------------------------

bool CacheLocText::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "locale", Locale );
	Success &= Writer.WriteProperty( "text", Text );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheLocText::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "locale", Locale );
	Success &= Reader.ReadProperty( "text", Text );

	return Success;
}

// -----------------------------------------------------------------------------

CachePosition::CachePosition()
	: Latitude( 0.0 )
	, Longitude( 0.0 )
	, Altitude( 0.0 )
	, Pitch( 0.0 )
	, Bank( 0.0 )
	, Heading( 0.0 )
	, AltitudeIsAGL( false )
{
}

// -----------------------------------------------------------------------------

bool CachePosition::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "latitude", Latitude );
	Success &= Writer.WriteProperty( "longitude", Longitude );
	Success &= Writer.WriteProperty( "altitude", Altitude );
	Success &= Writer.WriteProperty( "pitch", Pitch );
	Success &= Writer.WriteProperty( "bank", Bank );
	Success &= Writer.WriteProperty( "heading", Heading );
	Success &= Writer.WriteProperty( "altitude_is_agl", AltitudeIsAGL );

	return Success;
}

// -----------------------------------------------------------------------------

bool CachePosition::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "latitude", Latitude );
	Success &= Reader.ReadProperty( "longitude", Longitude );
	Success &= Reader.ReadProperty( "altitude", Altitude );
	Success &= Reader.ReadProperty( "pitch", Pitch );
	Success &= Reader.ReadProperty( "bank", Bank );
	Success &= Reader.ReadProperty( "heading", Heading );
	Success &= Reader.ReadProperty( "altitude_is_agl", AltitudeIsAGL );

	return Success;
}

// -----------------------------------------------------------------------------

CacheTrackerSettings::CacheTrackerSettings()
	: AlertDistance( 500.0f )
	, AcquireDistance( 50.0f )
{
}

// -----------------------------------------------------------------------------

bool CacheTrackerSettings::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "alert_distance", AlertDistance );
	Success &= Writer.WriteProperty( "acquire_distance", AcquireDistance );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheTrackerSettings::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "alert_distance", AlertDistance );
	Success &= Reader.ReadProperty( "acquire_distance", AcquireDistance );

	return Success;
}

// -----------------------------------------------------------------------------

CacheDefinition::CacheDefinition()
	: Metadata()
	, LocText()
	, Position()
	, Tracker()
{
}

// -----------------------------------------------------------------------------

bool CacheDefinition::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "meta", Metadata );
	Success &= Writer.WriteProperty( "loc_text", LocText );
	Success &= Writer.WriteProperty( "position", Position );
	Success &= Writer.WriteProperty( "tracker", Tracker );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheDefinition::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "meta", Metadata );
	Success &= Reader.ReadProperty( "loc_text", LocText );
	Success &= Reader.ReadProperty( "position", Position );
	Success &= Reader.ReadProperty( "tracker", Tracker );

	return Success;
}

// -----------------------------------------------------------------------------

CacheAuthor::CacheAuthor()
	: Id()
	, Name()
{
}

// -----------------------------------------------------------------------------

bool CacheAuthor::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "id" , Id );
	Success &= Writer.WriteProperty( "name", Name );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheAuthor::Deserialise( Utils::Serialisation::Reader& Reader )
{
	bool Success = true;

	Success &= Reader.ReadProperty( "id", Id );
	Success &= Reader.ReadProperty( "name", Name );

	return Success;
}

// -----------------------------------------------------------------------------

CacheDefinitionCollection::CacheDefinitionCollection()
	: Version()
	, CacheDefinitions()
	, Authors()
{
}

// -----------------------------------------------------------------------------

bool CacheDefinitionCollection::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	bool Success = true;

	Success &= Writer.WriteProperty( "version", Version );
	Success &= Writer.WriteProperty( "cache_definitions", CacheDefinitions );
	Success &= Writer.WriteProperty( "authors", Authors );

	return Success;
}

// -----------------------------------------------------------------------------

bool CacheDefinitionCollection::Deserialise( Utils::Serialisation::Reader& Reader )
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
