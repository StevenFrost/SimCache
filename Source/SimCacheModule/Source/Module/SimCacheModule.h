// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Subsystems/CacheManager/CacheManager.h"
#include "ViewModels/TrackerViewModel.h"

#include <SimConnect/SimConnectClient.h>
#include <Utils/Event/EventDispatcher.h>

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

	bool InitializeSimConnectClient();
	void UninitializeSimConnectClient();

	bool InitializeEventDispatchers();
	void UninitializeEventDispatchers();

	bool InitializeTrackerViewModel();
	void UninitializeTrackerViewModel();

	bool InitializeCacheManager();
	void UninitializeCacheManager();

private:

	std::shared_ptr< SimConnect::ISimConnectClient >	SimConnectClient;
	std::shared_ptr< Utils::EventDispatcher >			JavaScriptEventDispatcher;

	std::unique_ptr< TrackerViewModel >					TrackerVM;

	std::unique_ptr< Subsystems::CacheManager >			CacheManager;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
