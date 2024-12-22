// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <SimConnect/SimConnectClient.h>
#include <Utils/Event/EventDispatcher.h>

// -----------------------------------------------------------------------------

namespace Utils
{
	typedef EventDispatcher NativeEventDispatcher;
}

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

class AircraftTracker
{
public:

	AircraftTracker(
		Utils::NativeEventDispatcher& InternalEventDispatcher,
		SimConnect::ISimConnectClient& SimConnectClient
	);

	bool Initialize();
	void Uninitialize();

private:

	bool RegisterAircraftPositionUpdatedEvent();
	void UnregisterAircraftPositionUpdatedEvent();

	void OnAircraftPositionUpdated( const Utils::EarthCoordinate CurrentPosition );

private:

	Utils::NativeEventDispatcher&	InternalEventDispatcher;
	SimConnect::ISimConnectClient&	SimConnectClient;

	SimConnect::Handle				UserAircraftPositionUpdatedHandle;
};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
