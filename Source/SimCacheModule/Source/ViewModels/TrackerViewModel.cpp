// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/TrackerViewModel.h"

// -----------------------------------------------------------------------------

TrackerViewModel::TrackerViewModel( Utils::EventDispatcher& ViewEventDispatcher )
	: ViewModel( ViewEventDispatcher )
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
}

// -----------------------------------------------------------------------------

void TrackerViewModel::UnregisterEventListeners()
{
	if ( OnTrackerLoadedEventHandle.IsValid() )
	{
		GetViewEventDispatcher().UnregisterEventListener( OnTrackerLoadedEventHandle );
	}
}

// -----------------------------------------------------------------------------

void TrackerViewModel::OnTrackerLoaded( const TrackerLoadedEvent& Event )
{
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
