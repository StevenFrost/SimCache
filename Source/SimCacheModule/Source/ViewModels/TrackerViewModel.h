// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Events/TrackerLoadedEvent.h"
#include "ViewModels/ViewModel.h"

#include <Utils/Event/EventHandle.h>

// -----------------------------------------------------------------------------

class TrackerViewModel
	: public ViewModel
{
public:

	TrackerViewModel( Utils::EventDispatcher& ViewEventDispatcher );
	virtual ~TrackerViewModel();

	virtual bool Initialize() override final;
	virtual void Uninitialize() override final;

private:

	void RegisterEventListeners();
	void UnregisterEventListeners();

	void OnTrackerLoaded( const TrackerLoadedEvent& Event );

private:

	Utils::EventHandle OnTrackerLoadedEventHandle;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
