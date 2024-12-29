// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/CacheDefinitionCollection.h"
#include "Core/RangeAnnulus.h"

#include "Events/AircraftPositionUpdatedEvent.h"

#include "Subsystems/CacheDataStore/CacheDataStore.h"

#include <Utils/Event/NativeEventDispatcher.h>
#include <Utils/Geodesy/EarthCoordinate.h>
#include <Utils/Optional/Optional.h>

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

	const CacheDefinition* GetCurrentTrackedCache() const;
	bool SetCurrentTrackedCache( const CacheId& Id );
	void ClearCurrentTrackedCache();

	RangeAnnulus GetLastKnownAnnulus() const;

private:

	struct TrackedCacheState
	{
		TrackedCacheState( const CacheId& Id, const CacheTrackerSettings& TrackerSettings, const Utils::EarthCoordinate& GeocentricPosition );

		const CacheId Id;
		const CacheTrackerSettings TrackerSettings;
		const Utils::EarthCoordinate GeocentricPosition;
		RangeAnnulus Annulus;
		bool InsideAlertRange;
	};

private:

	void RegisterAircraftPositionUpdatedListener();
	void UnregisterAircraftPositionUpdatedListener();
	void OnAircraftPositionUpdated( const AircraftPositionUpdatedEvent& Event );

	void Update( const Utils::EarthCoordinate& CurrentPosition );

	bool UpdateAnnulus( TrackedCacheState& CacheState, const double RangeMeters );
	bool CheckAlertRange( TrackedCacheState& CacheState, const double RangeMeters );
	bool CheckAcquisitionRange( TrackedCacheState& CacheState, const double RangeMeters );

	RangeAnnulus GetAnnulus( const double RangeMeters ) const;

private:

	const Subsystems::CacheDataStore& CacheDataStore;
	Utils::NativeEventDispatcher& InternalEventDispatcher;

	Utils::EventHandle OnAircraftPositionUpdatedEventHandle;

	Utils::Optional< TrackedCacheState > CurrentTrackedCache;

};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
