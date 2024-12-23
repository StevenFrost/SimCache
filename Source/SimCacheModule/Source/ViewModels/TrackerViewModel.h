// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Events/CacheFoundEvent.h"
#include "Events/TrackerLoadedEvent.h"
#include "Events/TrackerStateUpdatedEvent.h"
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

	TrackerViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher, Subsystems::CacheTracker& CacheTracker );
	virtual ~TrackerViewModel();

	virtual bool Initialize() override final;
	virtual void Uninitialize() override final;

private:

	void RegisterEventListeners();
	void UnregisterEventListeners();

	void OnTrackerLoaded( const TrackerLoadedEvent& Event );
	void OnTrackerStateUpdated( const TrackerStateUpdatedEvent& Event );
	void OnCacheFound( const CacheFoundEvent& Event );

private:

	Subsystems::CacheTracker& CacheTracker;

	Utils::EventHandle OnTrackerLoadedEventHandle;
	Utils::EventHandle OnTrackerStateUpdatedEventHandle;
	Utils::EventHandle OnCacheFoundEventHandle;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
