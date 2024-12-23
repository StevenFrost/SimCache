// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/TrackerViewModel.h"

// -----------------------------------------------------------------------------

TrackerViewModel::TrackerViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher, Subsystems::CacheTracker& CacheTracker )
	: ViewModel( InternalEventDispatcher, ViewEventDispatcher )
	, CacheTracker( CacheTracker )
	, OnTrackerLoadedEventHandle()
	, OnTrackerStateUpdatedEventHandle()
	, OnCacheFoundEventHandle()
{
}

// -----------------------------------------------------------------------------

TrackerViewModel::~TrackerViewModel()
{
}

// -----------------------------------------------------------------------------

bool TrackerViewModel::Initialize()
{
	const bool ParentInitialized = ViewModel::Initialize();
	if ( !ParentInitialized )
	{
		return false;
	}

	RegisterEventListeners();

	return true;
}

// -----------------------------------------------------------------------------

void TrackerViewModel::Uninitialize()
{
	UnregisterEventListeners();

	ViewModel::Uninitialize();
}

// -----------------------------------------------------------------------------

void TrackerViewModel::RegisterEventListeners()
{
	OnTrackerLoadedEventHandle = GetViewEventDispatcher().RegisterEventListener< TrackerLoadedEvent >(
		[ & ]( const TrackerLoadedEvent& Event )
		{
			OnTrackerLoaded( Event );
		}
	);

	OnTrackerStateUpdatedEventHandle = GetInternalEventDispatcher().RegisterEventListener< TrackerStateUpdatedEvent >(
		[ & ]( const TrackerStateUpdatedEvent& Event )
		{
			OnTrackerStateUpdated( Event );
		}
	);

	OnCacheFoundEventHandle = GetInternalEventDispatcher().RegisterEventListener< CacheFoundEvent >(
		[ & ]( const CacheFoundEvent& Event )
		{
			OnCacheFound( Event );
		}
	);
}

// -----------------------------------------------------------------------------

void TrackerViewModel::UnregisterEventListeners()
{
	if ( OnTrackerStateUpdatedEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnTrackerStateUpdatedEventHandle );
	}

	if ( OnCacheFoundEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnCacheFoundEventHandle );
	}

	if ( OnTrackerLoadedEventHandle.IsValid() )
	{
		GetViewEventDispatcher().UnregisterEventListener( OnTrackerLoadedEventHandle );
	}
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnCacheFound( const CacheFoundEvent& Event )
{
	GetViewEventDispatcher().FireEvent( Event );
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnTrackerLoaded( const TrackerLoadedEvent& Event )
{
	// TODO: remove this placeholder
	CacheTracker.ForceNextTrackerStateUpdatedEvent = true;
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnTrackerStateUpdated( const TrackerStateUpdatedEvent& Event )
{
	GetViewEventDispatcher().FireEvent( Event );
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
