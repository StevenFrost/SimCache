// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <SimConnect/SimConnectClient.h>
#include <Utils/Event/EventDispatcher.h>

// -----------------------------------------------------------------------------

class SimCacheModule
{
public:

	SimCacheModule();
	~SimCacheModule();

	void Initialize();
	void Uninitialize();

private:

	void InitializeSimConnectClient();
	void UninitializeSimConnectClient();

	void InitializeEventDispatchers();
	void UninitializeEventDispatchers();

private:

	std::shared_ptr< SimConnect::ISimConnectClient >	SimConnectClient;
	std::shared_ptr< Utils::EventDispatcher >			JavaScriptEventDispatcher;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
