// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Events/AircraftPositionUpdatedEvent.h"
#include "Events/CacheAlertRangeEnteredEvent.h"
#include "Events/CacheFoundEvent.h"
#include "Events/TrackedCacheChangedEvent.h"
#include "Events/TrackerStateUpdatedEvent.h"
#include "Subsystems/CacheTracker/CacheTracker.h"

#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( CacheTracker, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

CacheTracker::TrackedCacheState::TrackedCacheState( const CacheId& Id, const CacheTrackerSettings& TrackerSettings, const Utils::EarthCoordinate& GeocentricPosition )
	: Id( Id )
	, TrackerSettings( TrackerSettings )
	, GeocentricPosition( GeocentricPosition )
	, State( TrackerState::OutOfRange )
	, InsideAlertRange( false )
{
}

// -----------------------------------------------------------------------------

CacheTracker::CacheTracker( Utils::NativeEventDispatcher& InternalEventDispatcher, const Subsystems::CacheManager& CacheManager )
	: CacheManager( CacheManager )
	, InternalEventDispatcher( InternalEventDispatcher )
	, OnAircraftPositionUpdatedEventHandle()
	, CurrentTrackedCache( nullptr )
	, ForceNextTrackerStateUpdatedEvent( false )
{
}

// -----------------------------------------------------------------------------

bool CacheTracker::Initialize()
{
	RegisterAircraftPositionUpdatedListener();
	return true;
}

// -----------------------------------------------------------------------------

void CacheTracker::Uninitialize()
{
	UnregisterAircraftPositionUpdatedListener();
}

// -----------------------------------------------------------------------------

void CacheTracker::RegisterAircraftPositionUpdatedListener()
{
	OnAircraftPositionUpdatedEventHandle = InternalEventDispatcher.RegisterEventListener< AircraftPositionUpdatedEvent >(
		[ & ]( const AircraftPositionUpdatedEvent& Event )
		{
			OnAircraftPositionUpdated( Event );
		}
	);
}

// -----------------------------------------------------------------------------

void CacheTracker::UnregisterAircraftPositionUpdatedListener()
{
	if ( OnAircraftPositionUpdatedEventHandle.IsValid() )
	{
		InternalEventDispatcher.UnregisterEventListener( OnAircraftPositionUpdatedEventHandle );
	}
}

// -----------------------------------------------------------------------------

void CacheTracker::OnAircraftPositionUpdated( const AircraftPositionUpdatedEvent& Event )
{
	UpdateTrackerState( Event.CurrentPosition );
}

// -----------------------------------------------------------------------------

void CacheTracker::ClearCurrentTrackedCache()
{
	CurrentTrackedCache = nullptr;
}

// -----------------------------------------------------------------------------

bool CacheTracker::SetCurrentTrackedCache( const CacheId& Id )
{
	const auto* CurrentCacheDefinition = CacheManager.GetCacheDefinitionById( Id );
	if ( !CurrentCacheDefinition )
	{
		LOG( CacheTracker, Error, "Unable to set current tracked cache: cache with ID '%s' not found.", Id.c_str() );
		return false;
	}

	if ( CurrentCacheDefinition->Position.AltitudeIsAGL )
	{
		LOG( CacheTracker, Error, "Tracking caches with AltitudeIsAGL is not currently supported." );
		return false;
	}

	ClearCurrentTrackedCache();

	const auto GeocentricPosition = Utils::EarthCoordinate::FromGeodetic(
		CurrentCacheDefinition->Position.Latitude,
		CurrentCacheDefinition->Position.Longitude,
		CurrentCacheDefinition->Position.Altitude
	);

	CurrentTrackedCache = std::make_unique< TrackedCacheState >( Id, CurrentCacheDefinition->Tracker, GeocentricPosition );

	InternalEventDispatcher.FireEvent( TrackedCacheChangedEvent( Id ) );

	return true;
}

// -----------------------------------------------------------------------------

void CacheTracker::UpdateTrackerState( const Utils::EarthCoordinate& CurrentPosition )
{
	if ( !CurrentTrackedCache )
	{
		return;
	}

	const auto Range = CurrentPosition.DistanceTo( CurrentTrackedCache->GeocentricPosition );

	const auto NewState = GetCurrentAnnulus( Range );
	if ( ForceNextTrackerStateUpdatedEvent || NewState != CurrentTrackedCache->State )
	{
		ForceNextTrackerStateUpdatedEvent = false;

		CurrentTrackedCache->State = NewState;

		// fires the event every time the annulus (TrackerState enum) changes
		InternalEventDispatcher.FireEvent( TrackerStateUpdatedEvent( CurrentTrackedCache->Id, NewState ) );
	}

	// TODO: handle range re-entry causing multiple alerts
	const auto InsideAlertRange = Range < CurrentTrackedCache->TrackerSettings.AlertDistance;
	if ( InsideAlertRange != CurrentTrackedCache->InsideAlertRange )
	{
		CurrentTrackedCache->InsideAlertRange = Range;
		if ( InsideAlertRange )
		{
			// fires the event every time the user enters the alert range (but not when exiting)
			InternalEventDispatcher.FireEvent( CacheAlertRangeEnteredEvent( CurrentTrackedCache->Id ) );
		}
	}

	if ( Range < CurrentTrackedCache->TrackerSettings.AcquireDistance )
	{
		// one-shot event (since CurrentTrackedCache gets nulled out)
		InternalEventDispatcher.FireEvent( CacheFoundEvent( CurrentTrackedCache->Id ) );
		ClearCurrentTrackedCache();
	}
}

// -----------------------------------------------------------------------------

TrackerState CacheTracker::GetCurrentAnnulus( const double RangeMeters ) const
{
	if ( RangeMeters < 0.0 )
	{
		LOG( CacheTracker, Error, "Invalid range %f while determining current annulus.", RangeMeters );
	}

	if ( RangeMeters < 3704.0 )
	{
		return TrackerState::Annulus1;
	}

	if ( RangeMeters < 9260.0 )
	{
		return TrackerState::Annulus2;
	}

	if ( RangeMeters < 18520.0 )
	{
		return TrackerState::Annulus3;
	}

	if ( RangeMeters < 46300.0 )
	{
		return TrackerState::Annulus4;
	}

	return TrackerState::OutOfRange;
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
