// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Subsystems/Progression/Progression.h"

#include <Utils/Logging/Log.h>
#include <Utils/Serialisation/JSON/JSONReader.h>
#include <Utils/Serialisation/JSON/JSONWriter.h>

#include <fstream>
#include <sstream>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( Progression, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

Progression::Progression( Utils::NativeEventDispatcher& InternalEventDispatcher )
	: InternalEventDispatcher( InternalEventDispatcher )
	, OnCacheFoundEventHandle()
	, ProgressionPath( R"(\work\progression.json)" )
	, ProgressionData()
{
}

// -----------------------------------------------------------------------------

bool Progression::Initialize()
{
	LoadProgressionData();
	RegisterCacheFoundListener();

	return true;
}

// -----------------------------------------------------------------------------

void Progression::Uninitialize()
{
	UnregisterCacheFoundListener();
}

// -----------------------------------------------------------------------------

const Utils::DateTime* Progression::GetCacheAcquisitionTime( const CacheId& Id ) const
{
	const auto* CacheMetadata = ProgressionData.GetAcquiredCacheMetadata( Id );
	if ( CacheMetadata )
	{
		return &CacheMetadata->TimeAcquired;
	}
	return nullptr;
}

// -----------------------------------------------------------------------------

void Progression::LoadProgressionData()
{
	std::ifstream InputFileStream( ProgressionPath );

	if ( !InputFileStream.is_open() )
	{
		LOG( Progression, Warning, "Failed to open file '%s'.", ProgressionPath.c_str() );
		return;
	}

	std::ostringstream StringStream;
	StringStream << InputFileStream.rdbuf();
	InputFileStream.close();

	Utils::Serialisation::JSONReader Reader( StringStream.str() );
	if ( !ProgressionData.Deserialise( Reader ) )
	{
		LOG( Progression, Error, "Failed to deserialize progression data." );
	}
}

// -----------------------------------------------------------------------------

bool Progression::SaveProgressionData()
{
	Utils::Serialisation::JSONWriter Writer;
	if ( !ProgressionData.Serialise( Writer ) )
	{
		LOG( Progression, Error, "Failed to serialize progression data." );
		return false;
	}

	std::ofstream OutputFileStream( ProgressionPath );
	OutputFileStream << Writer.ToString();
	OutputFileStream.close();

	return true;
}

// -----------------------------------------------------------------------------

void Progression::RegisterCacheFoundListener()
{
	OnCacheFoundEventHandle = InternalEventDispatcher.RegisterEventListener< CacheFoundEvent >(
		[ & ]( const CacheFoundEvent& Event )
		{
			OnCacheFound( Event );
		}
	);
}

// -----------------------------------------------------------------------------

void Progression::UnregisterCacheFoundListener()
{
	if ( OnCacheFoundEventHandle.IsValid() )
	{
		InternalEventDispatcher.UnregisterEventListener( OnCacheFoundEventHandle );
	}
}

// -----------------------------------------------------------------------------

void Progression::OnCacheFound( const CacheFoundEvent& Event )
{
	if ( ProgressionData.AddAcquiredCacheMetadata( AcquiredCacheMetadata( Event.Id, Utils::DateTime::Now() ) ) )
	{
		SaveProgressionData();
	}
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
