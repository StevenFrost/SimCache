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

void SimCacheModule::Initialize()
{
	InitializeSimConnectClient();
	InitializeEventDispatchers();
}

// -----------------------------------------------------------------------------

void SimCacheModule::Uninitialize()
{
	UninitializeSimConnectClient();
	UninitializeEventDispatchers();
}

// -----------------------------------------------------------------------------

void SimCacheModule::InitializeSimConnectClient()
{
	SimConnectClient = SimConnect::MakeSimConnectClient( "SimCache" );
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

void SimCacheModule::InitializeEventDispatchers()
{
	JavaScriptEventDispatcher = Utils::MakeWASMEventDispatcher( Utils::EWASMEventDispatcherTarget::JavaScript );
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
