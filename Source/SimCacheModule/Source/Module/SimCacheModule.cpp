// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimCacheModule.h"

#include "Core/CacheDefinitionCollection.h"

#include <Utils/Event/NativeEventDispatcher.h>
#include <Utils/Event/WASMEventDispatcher.h>
#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( SimCacheModule, Info )

// -----------------------------------------------------------------------------

SimCacheModule::SimCacheModule()
	: SimConnectClient( nullptr )
	, UIEventDispatcher( nullptr )
	, InternalEventDispatcher( nullptr )
	, AircraftTracker( nullptr )
	, CacheDataStore( nullptr )
	, CacheObjectManager( nullptr )
	, TrackerVM( nullptr )
	, FrontEndVM( nullptr )
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

	if ( !InitializeCacheDataStore() )
	{
		return false;
	}

	if ( !InitializeCacheObjectManager() )
	{
		return false;
	}

	if ( !InitializeProgression() )
	{
		return false;
	}

	if ( !InitializeCacheTracker() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeSubSystems()
{
	UninitializeCacheTracker();
	UninitializeProgression();
	UninitializeCacheObjectManager();
	UninitializeCacheDataStore();
	UninitializeAircraftTracker();
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeViewModels()
{
	if ( !InitializeTrackerViewModel() )
	{
		return false;
	}

	if ( !InitializeFrontEndViewModel() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeViewModels()
{
	UninitializeFrontEndViewModel();
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
	InternalEventDispatcher = Utils::MakeNativeEventDispatcher();
	if ( !InternalEventDispatcher )
	{
		return false;
	}

	UIEventDispatcher = Utils::MakeWASMEventDispatcher( Utils::EWASMEventDispatcherTarget::JavaScript );
	if ( !UIEventDispatcher )
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

	if ( UIEventDispatcher )
	{
		UIEventDispatcher = nullptr;
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

	auto* UIEventDispatcherPtr = UIEventDispatcher.get();
	if ( !UIEventDispatcherPtr )
	{
		return false;
	}

	auto* CacheDataStorePtr = CacheDataStore.get();
	if ( !CacheDataStorePtr )
	{
		return false;
	}

	auto* CacheTrackerPtr = CacheTracker.get();
	if ( !CacheTrackerPtr )
	{
		return false;
	}

	TrackerVM = std::make_unique< TrackerViewModel >( *InternalEventDispatcherPtr , *UIEventDispatcherPtr, *CacheDataStorePtr, *CacheTrackerPtr );
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

bool SimCacheModule::InitializeFrontEndViewModel()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		return false;
	}

	auto* UIEventDispatcherPtr = UIEventDispatcher.get();
	if ( !UIEventDispatcherPtr )
	{
		return false;
	}

	auto* CacheDataStorePtr = CacheDataStore.get();
	if ( !CacheDataStorePtr )
	{
		return false;
	}

	auto* CacheTrackerPtr = CacheTracker.get();
	if ( !CacheTrackerPtr )
	{
		return false;
	}

	FrontEndVM = std::make_unique< FrontEndViewModel >( *InternalEventDispatcherPtr, *UIEventDispatcherPtr, *CacheDataStorePtr, *CacheTrackerPtr );
	if ( !FrontEndVM )
	{
		return false;
	}

	return FrontEndVM->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeFrontEndViewModel()
{
	if ( !FrontEndVM )
	{
		return;
	}

	FrontEndVM->Uninitialize();
	FrontEndVM = nullptr;
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

bool SimCacheModule::InitializeCacheDataStore()
{
	CacheDataStore = std::make_unique< Subsystems::CacheDataStore >();
	if ( !CacheDataStore )
	{
		return false;
	}

	return CacheDataStore->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeCacheDataStore()
{
	if ( !CacheDataStore )
	{
		return;
	}

	CacheDataStore->Uninitialize();
	CacheDataStore = nullptr;
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeCacheTracker()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Cache Tracker - invalid internal event dispatcher." );
		return false;
	}

	auto* CacheDataStorePtr = CacheDataStore.get();
	if ( !CacheDataStorePtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Cache Tracker - invalid Cache Data Store." );
		return false;
	}

	CacheTracker = std::make_unique< Subsystems::CacheTracker >( *InternalEventDispatcherPtr, *CacheDataStorePtr );
	if ( !CacheTracker )
	{
		return false;
	}

	return CacheTracker->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeCacheTracker()
{
	if ( !CacheTracker )
	{
		return;
	}

	CacheTracker->Uninitialize();
	CacheTracker = nullptr;
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeCacheObjectManager()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Cache Object Manager - invalid internal event dispatcher." );
		return false;
	}

	auto* SimConnectClientPtr = SimConnectClient.get();
	if ( !SimConnectClientPtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Cache Object Manager - invalid SimConnect client." );
		return false;
	}

	auto* CacheDataStorePtr = CacheDataStore.get();
	if ( !CacheDataStorePtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Cache Object Manager - invalid Cache Data Store." );
		return false;
	}

	CacheObjectManager = std::make_unique< Subsystems::CacheObjectManager >( *InternalEventDispatcherPtr, *SimConnectClientPtr, *CacheDataStorePtr );
	if ( !CacheObjectManager )
	{
		return false;
	}

	return CacheObjectManager->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeCacheObjectManager()
{
	if ( !CacheObjectManager )
	{
		return;
	}

	CacheObjectManager->Uninitialize();
	CacheObjectManager = nullptr;
}

// -----------------------------------------------------------------------------

bool SimCacheModule::InitializeProgression()
{
	auto* InternalEventDispatcherPtr = InternalEventDispatcher.get();
	if ( !InternalEventDispatcherPtr )
	{
		LOG( SimCacheModule, Error, "Failed to initialize Progression subsystem - invalid internal event dispatcher." );
		return false;
	}

	Progression = std::make_unique< Subsystems::Progression >( *InternalEventDispatcherPtr );
	if ( !Progression )
	{
		return false;
	}

	return Progression->Initialize();
}

// -----------------------------------------------------------------------------

void SimCacheModule::UninitializeProgression()
{
	if ( !Progression )
	{
		return;
	}

	Progression->Uninitialize();
	Progression = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
