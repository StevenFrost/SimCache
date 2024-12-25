// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"
#include "Core/TrackerState.h"

#include "Events/AircraftPositionUpdatedEvent.h"

#include "Subsystems/CacheDataStore/CacheDataStore.h"

#include <Utils/Event/EventDispatcher.h>
#include <Utils/Geodesy/EarthCoordinate.h>

#include <memory>

// -----------------------------------------------------------------------------

namespace Utils
{
typedef EventDispatcher NativeEventDispatcher;
}

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

class CacheTracker
{
public:

	CacheTracker( Utils::NativeEventDispatcher& InternalEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore );

	bool Initialize();
	void Uninitialize();

	bool SetCurrentTrackedCache( const CacheId& Id );
	void ClearCurrentTrackedCache();

private:

	void RegisterAircraftPositionUpdatedListener();
	void UnregisterAircraftPositionUpdatedListener();
	void OnAircraftPositionUpdated( const AircraftPositionUpdatedEvent& Event );

	void UpdateTrackerState( const Utils::EarthCoordinate& CurrentPosition );

	TrackerState GetCurrentAnnulus( const double RangeMeters ) const;

private:

	struct TrackedCacheState
	{
		TrackedCacheState( const CacheId& Id, const CacheTrackerSettings& TrackerSettings, const Utils::EarthCoordinate& GeocentricPosition );

		const CacheId Id;
		const CacheTrackerSettings TrackerSettings;
		const Utils::EarthCoordinate GeocentricPosition;
		TrackerState State;
		bool InsideAlertRange;
	};

private:

	const Subsystems::CacheDataStore& CacheDataStore;
	Utils::NativeEventDispatcher& InternalEventDispatcher;

	Utils::EventHandle OnAircraftPositionUpdatedEventHandle;

	std::unique_ptr< TrackedCacheState > CurrentTrackedCache;

public:

	bool ForceNextTrackerStateUpdatedEvent;

};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
