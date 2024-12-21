// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimCacheModule.h"

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/WASMEventDispatcher.h>
#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( SimCacheModule, Info )

// -----------------------------------------------------------------------------

SimCacheModule::SimCacheModule()
	: InternalEventDispatcher( nullptr )
	, SimConnectClient( nullptr )
	, JavaScriptEventDispatcher( nullptr )
	, AircraftTracker( nullptr )
	, CacheManager( nullptr )
	, TrackerVM( nullptr )
{
}

// -----------------------------------------------------------------------------

SimCacheModule::~SimCacheModule()
{
}

// -----------------------------------------------------------------------------

bool SimCacheModule::Initialize()
{
	if ( !InitializeSimConnectClient() )
	{
		return false;
	}

	if ( !InitializeEventDispatchers() )
	{
		return false;
	}

	if ( !InitializeSubSystems() )
	{
		return false;
	}

	if ( !InitializeViewModels() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::Uninitialize()
{
	UninitializeViewModels();
	UninitializeSubSystems();
	UninitializeEventDispatchers();
	UninitializeSimConnectClient();
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeSubSystems()
{
	if ( !InitializeAircraftTracker() )
	{
		return false;
	}

	if ( !InitializeCacheManager() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeSubSystems()
{
	UninitializeCacheManager();
	UninitializeAircraftTracker();
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeViewModels()
{
	if ( !InitializeTrackerViewModel() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeViewModels()
{
	UninitializeTrackerViewModel();
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
	// TODO: replace with NativeEventDispatcher instead of using WASMEventDispatcher with WASM/self target
	InternalEventDispatcher = Utils::MakeWASMEventDispatcher( Utils::EWASMEventDispatcherTarget::Self );
	if ( !InternalEventDispatcher )
	{
		return false;
	}

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
	if ( InternalEventDispatcher )
	{
		InternalEventDispatcher = nullptr;
	}

	if ( JavaScriptEventDispatcher )
	{
		JavaScriptEventDispatcher = nullptr;
	}
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeTrackerViewModel()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		return false;
	}

	auto* JavaScriptEventDispatcherPtr = JavaScriptEventDispatcher.get();
	if ( !JavaScriptEventDispatcherPtr )
	{
		return false;
	}

	TrackerVM = std::make_unique< TrackerViewModel >( *InternalEventDispatcherPtr , *JavaScriptEventDispatcherPtr );
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

bool SimCacheModule::InitializeAircraftTracker()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		return false;
	}

	auto* SimConnectClientPtr = SimConnectClient.get();
	if ( !SimConnectClientPtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Aircraft Tracker - invalid SimConnect client." );
		return false;
	}

	AircraftTracker = std::make_unique< Subsystems::AircraftTracker >( *InternalEventDispatcherPtr, *SimConnectClientPtr );
	if ( !AircraftTracker )
	{
		LOG( SimCacheModule, Error, "Failed to create Aircraft Tracker." );
		return false;
	}

	return AircraftTracker->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeAircraftTracker()
{
	if ( !AircraftTracker )
	{
		return;
	}

	AircraftTracker->Uninitialize();
	AircraftTracker = nullptr;
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
