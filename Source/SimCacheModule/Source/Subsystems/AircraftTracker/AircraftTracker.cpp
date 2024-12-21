// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Subsystems/AircraftTracker/AircraftTracker.h"

#include "Events/AircraftPositionUpdatedEvent.h"

#include <utility>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( AircraftTracker, Info )

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

AircraftTracker::AircraftTracker(
	Utils::NativeEventDispatcher& InternalEventDispatcher,
	SimConnect::ISimConnectClient& SimConnectClient
)
	: InternalEventDispatcher( InternalEventDispatcher )
	, SimConnectClient( SimConnectClient )
	, UserAircraftPositionUpdatedHandle()
{
}

// -----------------------------------------------------------------------------

bool AircraftTracker::Initialize()
{
	// TODO: Only bind the position updated event when we have a tracked cache
	if ( !RegisterAircraftPositionUpdatedEvent() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void AircraftTracker::Uninitialize()
{
	UnregisterAircraftPositionUpdatedEvent();
}

// -----------------------------------------------------------------------------

bool AircraftTracker::RegisterAircraftPositionUpdatedEvent()
{
	auto Callback = std::bind( &AircraftTracker::OnAircraftPositionUpdated, this, std::placeholders::_1 );
	UserAircraftPositionUpdatedHandle = SimConnectClient.RegisterUserAircraftPositionListener( std::move( Callback ) );

	if ( !UserAircraftPositionUpdatedHandle.IsValid() )
	{
		LOG( AircraftTracker, Error, "Failed to register user aircraft position listener." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void AircraftTracker::UnregisterAircraftPositionUpdatedEvent()
{
	if ( UserAircraftPositionUpdatedHandle.IsValid() )
	{
		SimConnectClient.UnregisterUserAircraftPositionListener( UserAircraftPositionUpdatedHandle );
	}
}

// -----------------------------------------------------------------------------

void AircraftTracker::OnAircraftPositionUpdated( const Utils::EarthCoordinate CurrentPosition )
{
	InternalEventDispatcher.FireEvent( AircraftPositionUpdatedEvent() );
}

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
