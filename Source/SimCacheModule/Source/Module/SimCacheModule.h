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

	bool Initialize();
	void Uninitialize();

private:

	bool InitializeSimConnectClient();
	void UninitializeSimConnectClient();

	bool InitializeEventDispatchers();
	void UninitializeEventDispatchers();

private:

	std::shared_ptr< SimConnect::ISimConnectClient >	SimConnectClient;
	std::shared_ptr< Utils::EventDispatcher >			JavaScriptEventDispatcher;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
