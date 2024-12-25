// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Subsystems/CacheDataStore/CacheDataStore.h"

#include <Utils/Logging/Log.h>
#include <Utils/Serialisation/JSON/JSONReader.h>

#include <fstream>
#include <sstream>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( CacheDataStore, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

CacheDataStore::CacheDataStore()
	: BaseCacheDefinitionCollection()
{
}

// -----------------------------------------------------------------------------

bool CacheDataStore::Initialize()
{
	if ( !InitializeBaseCacheDefinitionCollection() )
	{
		LOG( CacheDataStore, Error, "Failed to initialize base cache definition collection." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void CacheDataStore::Uninitialize()
{
}

// -----------------------------------------------------------------------------

const std::vector< CacheDefinition >& CacheDataStore::GetCacheDefinitions() const
{
	return BaseCacheDefinitionCollection.CacheDefinitions;
}

// -----------------------------------------------------------------------------

const CacheDefinition* CacheDataStore::GetCacheDefinitionById( const CacheId Id ) const
{
	for ( const auto& CacheDefinition : GetCacheDefinitions() )
	{
		if ( CacheDefinition.Metadata.Id == Id )
		{
			return &CacheDefinition;
		}
	}

	return nullptr;
}

// -----------------------------------------------------------------------------

bool CacheDataStore::InitializeBaseCacheDefinitionCollection()
{
	std::string BaseCacheDefinitionPath = R"(.\Data\simcache.base.json)";
	std::ifstream FileStream( BaseCacheDefinitionPath );
	std::stringstream StringStream;

	if ( !FileStream.is_open() )
	{
		LOG( CacheDataStore, Error, "Failed to open file '%s'.", BaseCacheDefinitionPath.c_str() );
		return false;
	}

	StringStream << FileStream.rdbuf();
	FileStream.close();

	Utils::Serialisation::JSONReader Reader( StringStream.str() );
	return BaseCacheDefinitionCollection.Deserialise( Reader );
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
