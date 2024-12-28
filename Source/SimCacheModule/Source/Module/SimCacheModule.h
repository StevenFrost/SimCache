// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Subsystems/AircraftTracker/AircraftTracker.h"
#include "Subsystems/CacheDataStore/CacheDataStore.h"
#include "Subsystems/CacheTracker/CacheTracker.h"
#include "Subsystems/CacheObjectManager/CacheObjectManager.h"
#include "ViewModels/TrackerViewModel.h"

#include <SimConnect/SimConnectClient.h>
#include <Utils/Event/EventDispatcher.h>
#include <Utils/WASM/Macros.h>

#include <memory>

// -----------------------------------------------------------------------------

class SimCacheModule
{
public:

	SimCacheModule();
	~SimCacheModule();

	bool Initialize();
	void Uninitialize();

private:

	bool InitializeSubSystems();
	void UninitializeSubSystems();

	bool InitializeViewModels();
	void UninitializeViewModels();

	bool InitializeSimConnectClient();
	void UninitializeSimConnectClient();

	bool InitializeEventDispatchers();
	void UninitializeEventDispatchers();

	bool InitializeTrackerViewModel();
	void UninitializeTrackerViewModel();

	bool InitializeAircraftTracker();
	void UninitializeAircraftTracker();

	bool InitializeCacheDataStore();
	void UninitializeCacheDataStore();

	bool InitializeCacheTracker();
	void UninitializeCacheTracker();

	bool InitializeCacheObjectManager();
	void UninitializeCacheObjectManager();

private:

	std::shared_ptr< SimConnect::ISimConnectClient >	SimConnectClient;

	std::unique_ptr< Utils::WASMEventDispatcher >		UIEventDispatcher;
	std::unique_ptr< Utils::NativeEventDispatcher >		InternalEventDispatcher;

	std::unique_ptr< Subsystems::AircraftTracker >		AircraftTracker;
	std::unique_ptr< Subsystems::CacheDataStore >		CacheDataStore;
	std::unique_ptr< Subsystems::CacheTracker >			CacheTracker;
	std::unique_ptr< Subsystems::CacheObjectManager >	CacheObjectManager;

	std::unique_ptr< TrackerViewModel >					TrackerVM;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
