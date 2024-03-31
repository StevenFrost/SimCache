// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimCacheModule.h"

#include <Utils/Event/WASMEventDispatcher.h>

// -----------------------------------------------------------------------------

SimCacheModule::SimCacheModule()
	: SimConnectClient( nullptr )
	, JavaScriptEventDispatcher( nullptr )
{
}

// -----------------------------------------------------------------------------

SimCacheModule::~SimCacheModule()
{
}

// -----------------------------------------------------------------------------

bool SimCacheModule::Initialize()
{
	const bool InitializeSimConnectClientSucceeded = InitializeSimConnectClient();
	if ( !InitializeSimConnectClientSucceeded )
	{
		return false;
	}

	const bool InitializeEventDispatchersSucceeded = InitializeEventDispatchers();
	if ( !InitializeEventDispatchersSucceeded )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::Uninitialize()
{
	UninitializeSimConnectClient();
	UninitializeEventDispatchers();
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeSimConnectClient()
{
	SimConnectClient = SimConnect::MakeSimConnectClient( "SimCache" );
	if ( !SimConnectClient )
	{
		return false;
	}

	return SimConnectClient->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeSimConnectClient()
{
	if ( !SimConnectClient )
	{
		return;
	}

	SimConnectClient->Uninitialize();
	SimConnectClient = nullptr;
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeEventDispatchers()
{
	JavaScriptEventDispatcher = Utils::MakeWASMEventDispatcher( Utils::EWASMEventDispatcherTarget::JavaScript );
	if ( !JavaScriptEventDispatcher )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeEventDispatchers()
{
	if ( !JavaScriptEventDispatcher )
	{
		return;
	}

	JavaScriptEventDispatcher = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
