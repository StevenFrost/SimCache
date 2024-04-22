// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <SimConnect/SimObject/SimObjectPosition.h>

#include <Utils/Geodesy/EarthCoordinate.h>
#include <Utils/Handle/Handle.h>
#include <Utils/WASM/Macros.h>

#include <MSFS/MSFS_WindowsTypes.h>

#include <functional>
#include <memory>
#include <string>

// -----------------------------------------------------------------------------

namespace SimConnect
{

// -----------------------------------------------------------------------------

typedef std::function< void( Utils::EarthCoordinate /* CurrentPosition */ ) > UserAircraftPositionUpdateFunc;
typedef std::function< void() > SimObjectCreatedFunc;

// -----------------------------------------------------------------------------

typedef Utils::Handle< DWORD > Handle;

// -----------------------------------------------------------------------------

class ISimConnectClient
{
public:

	virtual ~ISimConnectClient() = default;

	virtual bool Initialize() = 0;
	virtual bool Uninitialize() = 0;

	virtual bool IsConnected() const = 0;

	virtual SimConnect::Handle StartReceivingUserAircraftPositionUpdates( UserAircraftPositionUpdateFunc&& OnUserAircraftPositionUpdated ) = 0;
	virtual bool StopReceivingUserAircraftPositionUpdates( SimConnect::Handle& Handle ) = 0;

	virtual SimConnect::Handle CreateSimObject( const std::string& SimObjectTitle, const SimObjectPosition& Position, SimObjectCreatedFunc&& OnSimObjectCreated = nullptr ) = 0;
	virtual bool DestroySimObject( SimConnect::Handle& Handle ) = 0;
};

// -----------------------------------------------------------------------------

std::shared_ptr< ISimConnectClient > MakeSimConnectClient( const std::string& ApplicationName );

// -----------------------------------------------------------------------------

} // namespace SimConnect

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
