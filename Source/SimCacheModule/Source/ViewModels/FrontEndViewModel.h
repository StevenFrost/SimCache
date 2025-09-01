// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include "Core/UICacheDefinitionCollection.h"
#include "Events/CacheFoundEvent.h"
#include "Events/TrackedCacheChangedEvent.h"
#include "Events/UICacheSelectedEvent.h"
#include "Events/UIRequestAvailableCachesEvent.h"
#include "Subsystems/CacheTracker/CacheTracker.h"
#include "ViewModels/ViewModel.h"

#include <Utils/Event/EventHandle.h>

// -----------------------------------------------------------------------------

class FrontEndViewModel
	: public ViewModel
{
public:

	FrontEndViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::WASMEventDispatcher& UIEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore, Subsystems::CacheTracker& CacheTracker );
	virtual ~FrontEndViewModel();

	virtual bool Initialize() override final;
	virtual void Uninitialize() override final;

private:

	void RegisterEventListeners();
	void UnregisterEventListeners();

	void OnUIRequestAvailableCachesEvent( const UIRequestAvailableCachesEvent& Event );
	void OnUICacheSelectedEvent( const UICacheSelectedEvent& Event );

	void OnTrackedCacheChangedEvent( const TrackedCacheChangedEvent& Event );
	void OnCacheFound( const CacheFoundEvent& Event );

	UICacheDefinitionCollection BuildUICacheDefinitions() const;
	void SendUICacheListChangedEvent() const;

private:

	const Subsystems::CacheDataStore& CacheDataStore;
	Subsystems::CacheTracker& CacheTracker;

	Utils::EventHandle OnUIRequestAvailableCachesEventHandle;
	Utils::EventHandle OnUICacheSelectedEventHandle;
	Utils::EventHandle OnTrackedCacheChangedEventHandle;
	Utils::EventHandle OnCacheFoundEventHandle;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
