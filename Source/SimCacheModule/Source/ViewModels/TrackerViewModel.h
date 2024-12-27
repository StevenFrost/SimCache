// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Events/CacheFoundEvent.h"
#include "Events/RangeAnnulusChangedEvent.h"
#include "Events/TrackedCacheChangedEvent.h"
#include "Events/UITrackerLoadedEvent.h"
#include "Subsystems/CacheTracker/CacheTracker.h"
#include "ViewModels/ViewModel.h"

#include <Utils/Event/EventHandle.h>

// -----------------------------------------------------------------------------

namespace Utils
{
	typedef EventDispatcher NativeEventDispatcher;
}

// -----------------------------------------------------------------------------

class TrackerViewModel
	: public ViewModel
{
public:

	TrackerViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore, Subsystems::CacheTracker& CacheTracker );
	virtual ~TrackerViewModel();

	virtual bool Initialize() override final;
	virtual void Uninitialize() override final;

private:

	void RegisterEventListeners();
	void UnregisterEventListeners();

	void OnTrackerLoaded( const UITrackerLoadedEvent& Event );

	void OnTrackedCacheChangedEvent( const TrackedCacheChangedEvent& Event );
	void OnRangeAnnulusChanged( const RangeAnnulusChangedEvent& Event );
	void OnCacheFound( const CacheFoundEvent& Event );

	void SendUITrackedCacheChangedEvent( const CacheDefinition* Cache ) const;

private:

	const Subsystems::CacheDataStore& CacheDataStore;
	Subsystems::CacheTracker& CacheTracker;

	Utils::EventHandle OnTrackerLoadedEventHandle;
	Utils::EventHandle OnTrackedCacheChangedEventHandle;
	Utils::EventHandle OnRangeAnnulusChangedEventHandle;
	Utils::EventHandle OnCacheFoundEventHandle;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
