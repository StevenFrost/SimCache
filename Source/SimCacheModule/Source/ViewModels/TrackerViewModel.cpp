// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/TrackerViewModel.h"

#include "Events/UICacheFoundEvent.h"
#include "Events/UIRangeAnnulusChangedEvent.h"
#include "Events/UITrackerDataUpdateEvent.h"

// -----------------------------------------------------------------------------

TrackerViewModel::TrackerViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore, Subsystems::CacheTracker& CacheTracker )
	: ViewModel( InternalEventDispatcher, ViewEventDispatcher )
	, CacheDataStore( CacheDataStore )
	, CacheTracker( CacheTracker )
	, OnTrackerLoadedEventHandle()
	, OnTrackedCacheChangedEventHandle()
	, OnRangeAnnulusChangedEventHandle()
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
	OnTrackerLoadedEventHandle = GetViewEventDispatcher().RegisterEventListener< UITrackerLoadedEvent >(
		[ & ]( const UITrackerLoadedEvent& Event )
		{
			OnTrackerLoaded( Event );
		}
	);

	OnTrackedCacheChangedEventHandle = GetInternalEventDispatcher().RegisterEventListener< TrackedCacheChangedEvent >(
		[ & ]( const TrackedCacheChangedEvent& Event )
		{
			OnTrackedCacheChangedEvent( Event );
		}
	);

	OnRangeAnnulusChangedEventHandle = GetInternalEventDispatcher().RegisterEventListener< RangeAnnulusChangedEvent >(
		[ & ]( const RangeAnnulusChangedEvent& Event )
		{
			OnRangeAnnulusChanged( Event );
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
	if ( OnRangeAnnulusChangedEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnRangeAnnulusChangedEventHandle );
	}

	if ( OnTrackedCacheChangedEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnTrackedCacheChangedEventHandle );
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
	GetViewEventDispatcher().FireEvent( UICacheFoundEvent() );
}

// -----------------------------------------------------------------------------

void TrackerViewModel::SendUITrackerDataUpdateEvent( const CacheDefinition* Cache ) const
{
	if ( !Cache )
	{
		return;
	}

	const auto Annulus = CacheTracker.GetLastKnownAnnulus();

	// TODO: use appropriate localized text
	GetViewEventDispatcher().FireEvent( UITrackerDataUpdateEvent( Cache->LocText[ 0 ].Text.Title, Annulus ) );
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnTrackerLoaded( const UITrackerLoadedEvent& Event )
{
	// the tracker InGamePanel opened; send full tracked cache data
	SendUITrackerDataUpdateEvent( CacheTracker.GetCurrentTrackedCache() );
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnTrackedCacheChangedEvent( const TrackedCacheChangedEvent& Event )
{
	// tracked cache changed; send full tracked cache data
	SendUITrackerDataUpdateEvent( CacheDataStore.GetCacheDefinitionById( Event.NewCacheId ) );
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnRangeAnnulusChanged( const RangeAnnulusChangedEvent& Event )
{
	GetViewEventDispatcher().FireEvent( UIRangeAnnulusChangedEvent( Event ) );
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
