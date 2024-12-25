// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

class CacheDataStore
{
public:

	CacheDataStore();

	bool Initialize();
	void Uninitialize();

	const std::vector< CacheDefinition >& GetCacheDefinitions() const;
	const CacheDefinition* GetCacheDefinitionById( const CacheId Id ) const;

private:

	bool InitializeBaseCacheDefinitionCollection();

private:

	CacheDefinitionCollection BaseCacheDefinitionCollection;

};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
