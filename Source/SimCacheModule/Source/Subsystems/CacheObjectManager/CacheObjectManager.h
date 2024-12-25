// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Subsystems/CacheDataStore/CacheDataStore.h"

#include <SimConnect/SimConnectClient.h>
#include <Utils/Event/EventDispatcher.h>
#include <Utils/Event/EventHandle.h>

// -----------------------------------------------------------------------------

namespace Utils
{
	typedef EventDispatcher NativeEventDispatcher;
}

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

class CacheObjectManager
{
public:

	CacheObjectManager(
		Utils::NativeEventDispatcher& InternalEventDispatcher,
		SimConnect::ISimConnectClient& SimConnectClient,
		Subsystems::CacheDataStore& CacheDataStore
	);

	bool Initialize();
	void Uninitialize();

private:

	bool RegisterTrackedCacheChangedEvent();
	void UnregisterTrackedCacheChangedEvent();

	bool RegisterCacheFoundEvent();
	void UnregisterCacheFoundEvent();

	void OnTrackedCacheChanged( const CacheId& NewCacheId );
	void OnCacheFound();

	bool CreateCacheObject( const CacheId& CacheId );
	void DestroyCacheObject();

private:

	Utils::NativeEventDispatcher&	InternalEventDispatcher;
	SimConnect::ISimConnectClient&	SimConnectClient;
	Subsystems::CacheDataStore&		CacheDataStore;

	Utils::EventHandle				TrackedCacheChangedHandle;
	Utils::EventHandle				CacheFoundHandle;

	SimConnect::Handle				CacheObjectHandle;
};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
