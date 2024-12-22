// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Subsystems/CacheObjectManager/CacheObjectManager.h"

#include "Events/CacheFoundEvent.h"
#include "Events/TrackedCacheChangedEvent.h"

#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( CacheObjectManager, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

CacheObjectManager::CacheObjectManager(
	Utils::NativeEventDispatcher& InternalEventDispatcher,
	SimConnect::ISimConnectClient& SimConnectClient,
	Subsystems::CacheManager& CacheManager
)
	: InternalEventDispatcher( InternalEventDispatcher )
	, SimConnectClient( SimConnectClient )
	, CacheManager( CacheManager )
	, TrackedCacheChangedHandle()
	, CacheFoundHandle()
	, CacheObjectHandle()
{
}

// -----------------------------------------------------------------------------

bool CacheObjectManager::Initialize()
{
	if ( !RegisterTrackedCacheChangedEvent() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void CacheObjectManager::Uninitialize()
{
	UnregisterTrackedCacheChangedEvent();

	if ( CacheObjectHandle.IsValid() )
	{
		DestroyCacheObject();
	}
}

// -----------------------------------------------------------------------------

bool CacheObjectManager::RegisterTrackedCacheChangedEvent()
{
	TrackedCacheChangedHandle = InternalEventDispatcher.RegisterEventListener< TrackedCacheChangedEvent >(
		[ & ]( const TrackedCacheChangedEvent& Event )
		{
			OnTrackedCacheChanged( Event.NewCacheId );
		}
	);

	return TrackedCacheChangedHandle.IsValid();
}

// -----------------------------------------------------------------------------

void CacheObjectManager::UnregisterTrackedCacheChangedEvent()
{
	if ( TrackedCacheChangedHandle.IsValid() )
	{
		InternalEventDispatcher.UnregisterEventListener( TrackedCacheChangedHandle );
	}
}

// -----------------------------------------------------------------------------

bool CacheObjectManager::RegisterCacheFoundEvent()
{
	CacheFoundHandle = InternalEventDispatcher.RegisterEventListener< CacheFoundEvent >(
		[ & ]( const CacheFoundEvent& Event )
		{
			OnCacheFound();
		}
	);

	return CacheFoundHandle.IsValid();
}

// -----------------------------------------------------------------------------

void CacheObjectManager::UnregisterCacheFoundEvent()
{
	if ( CacheFoundHandle.IsValid() )
	{
		InternalEventDispatcher.UnregisterEventListener( CacheFoundHandle );
	}
}

// -----------------------------------------------------------------------------

void CacheObjectManager::OnTrackedCacheChanged( const CacheId& NewCacheId )
{
	if ( CacheObjectHandle.IsValid() )
	{
		DestroyCacheObject();
	}

	if ( !CreateCacheObject( NewCacheId ) )
	{
		LOG( CacheObjectManager, Error, "Failed to create cache object for cache '%s'", NewCacheId.c_str() );
	}
}

// -----------------------------------------------------------------------------

void CacheObjectManager::OnCacheFound()
{
	DestroyCacheObject();
}

// -----------------------------------------------------------------------------

bool CacheObjectManager::CreateCacheObject( const CacheId& CacheId )
{
	auto* CacheDefinition = CacheManager.GetCacheDefinitionById( CacheId );
	if ( !CacheDefinition )
	{
		LOG( CacheObjectManager, Error, "Failed to find cache definition with ID '%s'", CacheId.c_str() );
		return false;
	}

	SimConnect::SimObjectPosition Position {
		.Latitude = CacheDefinition->Position.Latitude,
		.Longitude = CacheDefinition->Position.Longitude,
		.Altitude = CacheDefinition->Position.Altitude,
		.Pitch = CacheDefinition->Position.Pitch,
		.Bank = CacheDefinition->Position.Bank,
		.Heading = CacheDefinition->Position.Heading
	};

	CacheObjectHandle = SimConnectClient.CreateSimObject( CacheDefinition->Metadata.SimObjectTitle, Position,
		[ CacheId ]()
		{
			LOG( CacheObjectManager, Info, "Cache '%s' created successfully", CacheId.c_str() );
		}
	);

	return true;
}

// -----------------------------------------------------------------------------

void CacheObjectManager::DestroyCacheObject()
{
	SimConnectClient.DestroySimObject( CacheObjectHandle );
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
