// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Events/AircraftPositionUpdatedEvent.h"

#include "Core/CacheDefinitionCollection.h"
#include "Core/TrackerState.h"

#include "Subsystems/CacheManager/CacheManager.h"

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

namespace CacheTrackerPrivate
{

// -----------------------------------------------------------------------------

struct TrackedCacheState
{
public:

	TrackedCacheState( const CacheId& Id, const CacheTrackerSettings& TrackerSettings, const Utils::EarthCoordinate& GeocentricPosition )
		: Id( Id )
		, TrackerSettings( TrackerSettings )
		, GeocentricPosition( GeocentricPosition )
		, State( TrackerState::OutOfRange )
		, InsideAlertRange( false )
	{}

public:

	const CacheId Id;
	const CacheTrackerSettings TrackerSettings;
	const Utils::EarthCoordinate GeocentricPosition;
	TrackerState State;
	bool InsideAlertRange;
};

// -----------------------------------------------------------------------------

} // namespace CacheTrackerPrivate

// -----------------------------------------------------------------------------

class CacheTracker
{
public:

	CacheTracker( Utils::NativeEventDispatcher& InternalEventDispatcher, const Subsystems::CacheManager& CacheManager );

	bool Initialize();
	void Uninitialize();

	bool SetCurrentTrackedCache( const CacheId& Id );
	void ClearCurrentTrackedCache();

private:

	void RegisterAircraftPositionUpdatedListener();
	void UnregisterAircraftPositionUpdatedListener();
	void OnAircraftPositionUpdated( const AircraftPositionUpdatedEvent& Event );

public:

	bool ForceNextTrackerStateUpdatedEvent = false;

private:

	void UpdateTrackerState( const Utils::EarthCoordinate& CurrentPosition );

	TrackerState GetCurrentAnnulus( const double RangeMeters ) const;

private:

	const Subsystems::CacheManager& CacheManager;
	Utils::NativeEventDispatcher& InternalEventDispatcher;

	Utils::EventHandle OnAircraftPositionUpdatedEventHandle;

	std::unique_ptr< CacheTrackerPrivate::TrackedCacheState > CurrentTrackedCache;

};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
