// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Events/AircraftPositionUpdatedEvent.h"
#include "Events/CacheAlertRangeEnteredEvent.h"
#include "Events/CacheFoundEvent.h"
#include "Events/RangeAnnulusChangedEvent.h"
#include "Events/TrackedCacheChangedEvent.h"
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
	, Annulus( RangeAnnulus::OutOfRange )
	, InsideAlertRange( false )
{
}

// -----------------------------------------------------------------------------

CacheTracker::CacheTracker( Utils::NativeEventDispatcher& InternalEventDispatcher, const Subsystems::CacheDataStore& CacheDataStore )
	: CacheDataStore( CacheDataStore )
	, InternalEventDispatcher( InternalEventDispatcher )
	, OnAircraftPositionUpdatedEventHandle()
	, CurrentTrackedCache()
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
	Update( Event.CurrentPosition );
}

// -----------------------------------------------------------------------------

void CacheTracker::ClearCurrentTrackedCache()
{
	CurrentTrackedCache = Utils::nullopt;
}

// -----------------------------------------------------------------------------

RangeAnnulus CacheTracker::GetLastKnownAnnulus() const
{
	if ( !CurrentTrackedCache )
	{
		return RangeAnnulus::OutOfRange;
	}

	return CurrentTrackedCache->Annulus;
}

// -----------------------------------------------------------------------------

const CacheDefinition* CacheTracker::GetCurrentTrackedCache() const
{
	if ( !CurrentTrackedCache )
	{
		return nullptr;
	}

	return CacheDataStore.GetCacheDefinitionById( CurrentTrackedCache->Id );
}

// -----------------------------------------------------------------------------

bool CacheTracker::SetCurrentTrackedCache( const CacheId& Id )
{
	const auto* CurrentCacheDefinition = CacheDataStore.GetCacheDefinitionById( Id );
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

	CurrentTrackedCache.emplace( Id, CurrentCacheDefinition->Tracker, GeocentricPosition );

	InternalEventDispatcher.FireEvent( TrackedCacheChangedEvent( Id ) );

	return true;
}

// -----------------------------------------------------------------------------

void CacheTracker::Update( const Utils::EarthCoordinate& CurrentPosition )
{
	if ( !CurrentTrackedCache )
	{
		return;
	}

	auto& CacheState = *CurrentTrackedCache;
	const auto Range = CurrentPosition.DistanceTo( CacheState.GeocentricPosition );

	UpdateAnnulus( CacheState, Range );
	CheckAlertRange( CacheState, Range );
	CheckAcquisitionRange( CacheState, Range );
}

// -----------------------------------------------------------------------------

bool CacheTracker::UpdateAnnulus( TrackedCacheState& CacheState, const double RangeMeters )
{
	const auto NewAnnulus = GetAnnulus( RangeMeters );
	if ( NewAnnulus != CacheState.Annulus )
	{
		CacheState.Annulus = NewAnnulus;

		// fires the event every time the annulus changes
		InternalEventDispatcher.FireEvent( RangeAnnulusChangedEvent( CacheState.Id, NewAnnulus ) );
		return true;
	}
	return false;
}

// -----------------------------------------------------------------------------

bool CacheTracker::CheckAlertRange( TrackedCacheState& CacheState, const double RangeMeters )
{
	// TODO: handle range re-entry causing multiple alerts
	const auto InsideAlertRange = RangeMeters < CacheState.TrackerSettings.AlertDistance;
	if ( InsideAlertRange != CacheState.InsideAlertRange )
	{
		CacheState.InsideAlertRange = InsideAlertRange;
		if ( InsideAlertRange )
		{
			// fires the event every time the user enters the alert range (but not when exiting)
			InternalEventDispatcher.FireEvent( CacheAlertRangeEnteredEvent( CacheState.Id ) );
			return true;
		}
	}
	return false;
}

// -----------------------------------------------------------------------------

bool CacheTracker::CheckAcquisitionRange( TrackedCacheState& CacheState, const double RangeMeters )
{
	if ( RangeMeters < CacheState.TrackerSettings.AcquireDistance )
	{
		// one-shot event (since CurrentTrackedCache gets nulled out)
		InternalEventDispatcher.FireEvent( CacheFoundEvent( CacheState.Id ) );
		ClearCurrentTrackedCache();
		return true;
	}
	return false;
}

// -----------------------------------------------------------------------------

RangeAnnulus CacheTracker::GetAnnulus( const double RangeMeters ) const
{
	if ( RangeMeters < 0.0 )
	{
		LOG( CacheTracker, Error, "Invalid range %f while determining current annulus.", RangeMeters );
	}

	if ( RangeMeters < 3704.0 )
	{
		return RangeAnnulus::Annulus1;
	}

	if ( RangeMeters < 9260.0 )
	{
		return RangeAnnulus::Annulus2;
	}

	if ( RangeMeters < 18520.0 )
	{
		return RangeAnnulus::Annulus3;
	}

	if ( RangeMeters < 46300.0 )
	{
		return RangeAnnulus::Annulus4;
	}

	return RangeAnnulus::OutOfRange;
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
