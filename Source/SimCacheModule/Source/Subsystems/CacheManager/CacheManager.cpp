// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Subsystems/CacheManager/CacheManager.h"

#include <Utils/Logging/Log.h>
#include <Utils/Serialisation/JSON/JSONReader.h>

#include <fstream>
#include <sstream>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( CacheManager, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

CacheManager::CacheManager()
	: BaseCacheDefinitionCollection()
{
}

// -----------------------------------------------------------------------------

bool CacheManager::Initialize()
{
	if ( !InitializeBaseCacheDefinitionCollection() )
	{
		LOG( CacheManager, Error, "Failed to initialize base cache definition collection." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void CacheManager::Uninitialize()
{
}

// -----------------------------------------------------------------------------

const std::vector< CacheDefinition >& CacheManager::GetCacheDefinitions() const
{
	return BaseCacheDefinitionCollection.CacheDefinitions;
}

// -----------------------------------------------------------------------------

const CacheDefinition* CacheManager::GetCacheDefinitionById( const CacheId Id ) const
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

bool CacheManager::InitializeBaseCacheDefinitionCollection()
{
	std::string BaseCacheDefinitionPath = R"(.\Data\simcache.base.json)";
	std::ifstream FileStream( BaseCacheDefinitionPath );
	std::stringstream StringStream;

	if ( !FileStream.is_open() )
	{
		LOG( CacheManager, Error, "Failed to open file '%s'.", BaseCacheDefinitionPath.c_str() );
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
