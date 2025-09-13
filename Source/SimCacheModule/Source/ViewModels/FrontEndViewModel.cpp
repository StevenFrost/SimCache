// Copyright (c) 2025 Steven Frost and Orion Lyau

#include "ViewModels/FrontEndViewModel.h"

#include "Events/UICacheFoundEvent.h"
#include "Events/UICacheListChangedEvent.h"
#include "Events/UIRangeAnnulusChangedEvent.h"
#include "Events/UITrackedCacheChangedEvent.h"
#include "Events/UITrackerDataUpdateEvent.h"

#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

FrontEndViewModel::FrontEndViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::WASMEventDispatcher& UIEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore, const Subsystems::Progression& Progression, Subsystems::CacheTracker& CacheTracker )
	: ViewModel( InternalEventDispatcher, UIEventDispatcher )
	, CacheDataStore( CacheDataStore )
	, Progression( Progression )
	, CacheTracker( CacheTracker )
	, OnUIRequestAvailableCachesEventHandle()
	, OnUICacheSelectedEventHandle()
	, OnTrackedCacheChangedEventHandle()
	, OnCacheFoundEventHandle()
{
}

// -----------------------------------------------------------------------------

FrontEndViewModel::~FrontEndViewModel()
{
}

// -----------------------------------------------------------------------------

bool FrontEndViewModel::Initialize()
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

void FrontEndViewModel::Uninitialize()
{
	UnregisterEventListeners();

	ViewModel::Uninitialize();
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::RegisterEventListeners()
{
	OnUIRequestAvailableCachesEventHandle = GetUIEventDispatcher().RegisterEventListener< UIRequestAvailableCachesEvent >(
		[ & ]( const UIRequestAvailableCachesEvent& Event )
		{
			OnUIRequestAvailableCachesEvent( Event );
		}
	);

	OnUICacheSelectedEventHandle = GetUIEventDispatcher().RegisterEventListener< UICacheSelectedEvent >(
		[ & ]( const UICacheSelectedEvent& Event )
		{
			OnUICacheSelectedEvent( Event );
		}
	);

	OnTrackedCacheChangedEventHandle = GetInternalEventDispatcher().RegisterEventListener< TrackedCacheChangedEvent >(
		[ & ]( const TrackedCacheChangedEvent& Event )
		{
			OnTrackedCacheChangedEvent( Event );
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

void FrontEndViewModel::UnregisterEventListeners()
{
	if ( OnUIRequestAvailableCachesEventHandle.IsValid() )
	{
		GetUIEventDispatcher().UnregisterEventListener( OnUIRequestAvailableCachesEventHandle );
	}

	if ( OnUICacheSelectedEventHandle.IsValid() )
	{
		GetUIEventDispatcher().UnregisterEventListener( OnUICacheSelectedEventHandle );
	}

	if ( OnTrackedCacheChangedEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnTrackedCacheChangedEventHandle );
	}

	if ( OnCacheFoundEventHandle.IsValid() )
	{
		GetInternalEventDispatcher().UnregisterEventListener( OnCacheFoundEventHandle );
	}
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::OnUIRequestAvailableCachesEvent( const UIRequestAvailableCachesEvent& Event )
{
	SendUICacheListChangedEvent();
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::OnUICacheSelectedEvent( const UICacheSelectedEvent& Event )
{
	CacheTracker.SetCurrentTrackedCache( Event.Id );
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::OnCacheFound( const CacheFoundEvent& Event )
{
	// refresh cache list (since it contains state on whether caches were found)
	SendUICacheListChangedEvent();
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::OnTrackedCacheChangedEvent( const TrackedCacheChangedEvent& Event )
{
	// send ID for currently tracked cache
	GetUIEventDispatcher().FireEvent( UITrackedCacheChangedEvent( Event.NewCacheId ) );
}

// -----------------------------------------------------------------------------

UICacheDefinitionCollection FrontEndViewModel::BuildUICacheDefinitions() const
{
	auto Caches = UICacheDefinitionCollection();
	Caches.Version = CacheDataStore.GetVersion();
	Caches.Authors = CacheDataStore.GetAuthors();
	std::transform(
		CacheDataStore.GetCacheDefinitions().cbegin(),
		CacheDataStore.GetCacheDefinitions().cend(),
		std::back_inserter( Caches.CacheDefinitions ),
		[ & ]( const CacheDefinition& Cache ) {
			auto UICache = UICacheDefinition();
			UICache.LocText = Cache.LocText[ 0 ]; // TODO: use localization subsystem
			UICache.Metadata = UICacheMetadata( Cache.Metadata, Progression.GetCacheAcquisitionTime( Cache.Metadata.Id ) );
			return UICache;
		}
	);
	return Caches;
}

// -----------------------------------------------------------------------------

void FrontEndViewModel::SendUICacheListChangedEvent() const
{
	auto UICacheDefinitions = BuildUICacheDefinitions();
	GetUIEventDispatcher().FireEvent( UICacheListChangedEvent( UICacheDefinitions ) );
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
