// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimCacheModule.h"

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/WASMEventDispatcher.h>

// -----------------------------------------------------------------------------

SimCacheModule::SimCacheModule()
	: SimConnectClient( nullptr )
	, JavaScriptEventDispatcher( nullptr )
	, TrackerVM( nullptr )
	, CacheManager( nullptr )
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

	const bool InitializeTrackerViewModelSucceeded = InitializeTrackerViewModel();
	if ( !InitializeTrackerViewModelSucceeded )
	{
		return false;
	}

	const bool InitializeCacheManagerSucceeded = InitializeCacheManager();
	if ( !InitializeCacheManagerSucceeded )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::Uninitialize()
{
	UninitializeCacheManager();
	UninitializeTrackerViewModel();
	UninitializeEventDispatchers();
	UninitializeSimConnectClient();
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

bool SimCacheModule::InitializeTrackerViewModel()
{
	auto* JavaScriptEventDispatcherPtr = JavaScriptEventDispatcher.get();
	if ( !JavaScriptEventDispatcherPtr )
	{
		return false;
	}

	TrackerVM = std::make_unique< TrackerViewModel >( *JavaScriptEventDispatcherPtr );
	if ( !TrackerVM )
	{
		return false;
	}

	return TrackerVM->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeTrackerViewModel()
{
	if ( !TrackerVM )
	{
		return;
	}

	TrackerVM->Uninitialize();
	TrackerVM = nullptr;
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeCacheManager()
{
	CacheManager = std::make_unique< Subsystems::CacheManager >();
	if ( !CacheManager )
	{
		return false;
	}

	return CacheManager->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeCacheManager()
{
	if ( !CacheManager )
	{
		return;
	}

	CacheManager->Uninitialize();
	CacheManager = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
