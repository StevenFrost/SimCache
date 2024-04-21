// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimConnectClient.h"

#include "DataDefinitions/AircraftPosition.h"
#include "DataDefinitions/SimConnectDataDefinitionId.h"

#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( SimConnectClient, Info )

// -----------------------------------------------------------------------------

namespace SimConnect
{

// -----------------------------------------------------------------------------

SimConnectClient::SimConnectClient( const std::string& ApplicationName )
	: ApplicationName( ApplicationName )
	, SimConnectHandle( INVALID_HANDLE_VALUE )
	, UserAircraftPositionUpdateRegistry()
	, SimObjectsPendingCreation()
	, CreatedSimObjects()
{
}

// -----------------------------------------------------------------------------

SimConnectClient::~SimConnectClient()
{
}

// -----------------------------------------------------------------------------

bool SimConnectClient::Initialize()
{
	if ( !OpenConnection() )
	{
		LOG( SimConnectClient, Error, "Failed to establish a connection with SimConnect." );
		return false;
	}

	if ( !RegisterCallbacks() )
	{
		LOG( SimConnectClient, Error, "Failed to register required SimConnect callbacks." );
		return false;
	}

	if ( !BuildDataDefinitions() )
	{
		LOG( SimConnectClient, Error, "Failed to build required data definitions." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::Uninitialize()
{
	if ( !CloseConnection() )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::IsConnected() const
{
	return SimConnectHandle != INVALID_HANDLE_VALUE;
}

// -----------------------------------------------------------------------------

SimConnect::Handle SimConnectClient::StartReceivingUserAircraftPositionUpdates( UserAircraftPositionUpdateFunc&& OnUserAircraftPositionUpdated )
{
	const auto DataRequestHandle = SimConnect::Handle::Make();

	const auto Result = SimConnect_RequestDataOnSimObject(
		SimConnectHandle,
		DataRequestHandle.GetId(),
		SimConnectDataDefinitionId::AircraftPosition,
		SIMCONNECT_OBJECT_ID_USER,
		SIMCONNECT_PERIOD_VISUAL_FRAME,
		SIMCONNECT_DATA_REQUEST_FLAG_CHANGED
	);

	if ( Result != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to request data 'UserAircraftPositionUpdate' on the user aircraft." );
		return Handle();
	}

	UserAircraftPositionUpdateRegistry.emplace( DataRequestHandle, OnUserAircraftPositionUpdated );

	return DataRequestHandle;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::StopReceivingUserAircraftPositionUpdates( SimConnect::Handle& Handle )
{
	if ( UserAircraftPositionUpdateRegistry.find( Handle ) == UserAircraftPositionUpdateRegistry.end() )
	{
		LOG( SimConnectClient, Error, "Failed to locate a user aircraft position update registration with handle %lu.", Handle.GetId() );
		return false;
	}

	const auto Result = SimConnect_RequestDataOnSimObject(
		SimConnectHandle,
		Handle.GetId(),
		SimConnectDataDefinitionId::AircraftPosition,
		SIMCONNECT_OBJECT_ID_USER,
		SIMCONNECT_PERIOD_NEVER
	);

	UserAircraftPositionUpdateRegistry.erase( Handle );
	Handle.Reset();

	if ( Result != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to request data 'UserAircraftPositionUpdate' on the user aircraft." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

SimConnect::Handle SimConnectClient::CreateSimObject( const std::string& SimObjectTitle, const SimObjectPosition& Position, SimObjectCreatedFunc&& OnSimObjectCreated )
{
	const auto RequestHandle = SimConnect::Handle::Make();
	
	SIMCONNECT_DATA_INITPOSITION SimObjectPosition;
	SimObjectPosition.Latitude = Position.Latitude;
	SimObjectPosition.Longitude = Position.Longitude;
	SimObjectPosition.Altitude = Position.Altitude;
	SimObjectPosition.Pitch = Position.Pitch;
	SimObjectPosition.Bank = Position.Bank;
	SimObjectPosition.Heading = Position.Heading;
	SimObjectPosition.OnGround = 0;
	SimObjectPosition.Airspeed = 0;

	const auto Result = SimConnect_AICreateSimulatedObject(
		SimConnectHandle,
		SimObjectTitle.c_str(),
		SimObjectPosition,
		RequestHandle.GetId()
	);

	if ( Result != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to request the creation of SimObject '%s'.", SimObjectTitle.c_str() );
		return Handle();
	}

	SimObjectsPendingCreation.emplace( RequestHandle, OnSimObjectCreated );

	return RequestHandle;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::DestroySimObject( SimConnect::Handle& Handle )
{
	if ( SimObjectsPendingCreation.find( Handle ) != SimObjectsPendingCreation.end() )
	{
		LOG( SimConnectClient, Error, "Cannot destroy a SimObject which is in the process of being created." );
		return false;
	}

	auto SimObject = CreatedSimObjects.find( Handle );
	if ( SimObject == CreatedSimObjects.end() )
	{
		LOG( SimConnectClient, Error, "Unable to locate created SimObject with handle %lu.", Handle.GetId() );
		return false;
	}

	const auto SimObjectId = SimObject->second;
	const auto Result = SimConnect_AIRemoveObject( SimConnectHandle, SimObjectId, Handle.GetId() );

	if ( Result != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to destroy SimObject %lu.", SimObjectId );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::OpenConnection()
{
	if ( SimConnect_Open( &SimConnectHandle, ApplicationName.c_str(), nullptr, 0, 0, 0 ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to open a new SimConnect connection." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::CloseConnection()
{
	if ( SimConnect_Close( SimConnectHandle ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to close the SimConnect connection." );
		return false;
	}

	SimConnectHandle = INVALID_HANDLE_VALUE;

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::RegisterCallbacks()
{
	if ( SimConnect_CallDispatch( SimConnectHandle, &SimConnectClient::DispatchProc, this ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to register DispatchProc function." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::BuildDataDefinitions()
{
	if ( !BuildAircraftPositionDataDefinition() )
	{
		LOG( SimConnectClient, Error, "Failed to build AircraftPosition data definition." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::BuildAircraftPositionDataDefinition()
{
	if ( SimConnect_AddToDataDefinition( SimConnectHandle, SimConnectDataDefinitionId::AircraftPosition, "Plane Latitude", "degrees" ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to add 'Plane Latitude' to 'AircraftPosition' data definition." );
		return false;
	}

	if ( SimConnect_AddToDataDefinition( SimConnectHandle, SimConnectDataDefinitionId::AircraftPosition, "Plane Longitude", "degrees" ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to add 'Plane Longitude' to 'AircraftPosition' data definition." );
		return false;
	}

	if ( SimConnect_AddToDataDefinition( SimConnectHandle, SimConnectDataDefinitionId::AircraftPosition, "Plane Altitude", "feet" ) != S_OK )
	{
		LOG( SimConnectClient, Error, "Failed to add 'Plane Altitude' to 'AircraftPosition' data definition." );
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

void SimConnectClient::OnConnectionOpen( const SIMCONNECT_RECV_OPEN& Data )
{
	LOG( SimConnectClient, Info, "Connected to %s. Simulator Version: %d.%d.%d.%d. SimConnect Version: %d.%d.%d.%d.",
		Data.szApplicationName,
		Data.dwApplicationVersionMajor,
		Data.dwApplicationVersionMinor,
		Data.dwApplicationBuildMajor,
		Data.dwApplicationBuildMinor,
		Data.dwSimConnectVersionMajor,
		Data.dwSimConnectVersionMinor,
		Data.dwSimConnectBuildMajor,
		Data.dwSimConnectBuildMinor
	);
}

// -----------------------------------------------------------------------------

void SimConnectClient::OnSimObjectCreated( const SIMCONNECT_RECV_ASSIGNED_OBJECT_ID& Data )
{
	const auto RequestHandle = SimConnect::Handle( Data.dwRequestID );

	auto SimObjectPendingCreation = SimObjectsPendingCreation.find( RequestHandle );
	if ( SimObjectPendingCreation == SimObjectsPendingCreation.end() )
	{
		LOG( SimConnectClient, Error, "Failed to find a SimConnect pending creation with handle %lu.", RequestHandle.GetId() );
		return;
	}

	CreatedSimObjects.emplace( RequestHandle, Data.dwObjectID );

	SimObjectPendingCreation->second();
	SimObjectsPendingCreation.erase( SimObjectPendingCreation );
}

// -----------------------------------------------------------------------------

void SimConnectClient::OnReceivedSimObjectData( const SIMCONNECT_RECV_SIMOBJECT_DATA& Data )
{
	const auto DataRequestHandle = SimConnect::Handle( Data.dwRequestID );

	auto AircraftPositionUpdateRegistration = UserAircraftPositionUpdateRegistry.find( DataRequestHandle );
	if ( AircraftPositionUpdateRegistration == UserAircraftPositionUpdateRegistry.end() )
	{
		LOG( SimConnectClient, Error, "Failed to find a registered aircraft position update function with handle %lu.", DataRequestHandle.GetId() );
		return;
	}

	const auto* AircraftPositionData = reinterpret_cast< const AircraftPositionDataDefinition* >( &Data.dwData );
	if ( !AircraftPositionData )
	{
		LOG( SimConnectClient, Error, "Received SimObject data update for object %lu but the data was invalid.", Data.dwObjectID );
		return;
	}

	const auto CurrentPosition = Utils::EarthCoordinate::FromGeodetic(
		AircraftPositionData->Latitude,
		AircraftPositionData->Longitude,
		AircraftPositionData->Altitude
	);

	AircraftPositionUpdateRegistration->second( CurrentPosition );
}

// -----------------------------------------------------------------------------

void SimConnectClient::DispatchProc( SIMCONNECT_RECV* Data, DWORD DataSizeBytes, void* Context )
{
	auto* Client = static_cast< SimConnectClient* >( Context );
	if ( !Client )
	{
		LOG( SimConnectClient, Error, "DispatchProc - Invalid context." );
		return;
	}

	if ( !Data )
	{
		LOG( SimConnectClient, Error, "DispatchProc - Invalid Data." );
		return;
	}

	switch ( Data->dwID )
	{
	case SIMCONNECT_RECV_ID_OPEN:
		Client->OnConnectionOpen( *static_cast< SIMCONNECT_RECV_OPEN* >( Data ) );
		break;
	case SIMCONNECT_RECV_ID_ASSIGNED_OBJECT_ID:
		Client->OnSimObjectCreated( *static_cast< SIMCONNECT_RECV_ASSIGNED_OBJECT_ID* >( Data ) );
		break;
	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
		Client->OnReceivedSimObjectData( *static_cast< SIMCONNECT_RECV_SIMOBJECT_DATA* >( Data ) );
		break;
	}
}

// -----------------------------------------------------------------------------

std::shared_ptr< ISimConnectClient > MakeSimConnectClient( const std::string& ApplicationName )
{
	return std::make_shared< SimConnectClient >( ApplicationName );
}

// -----------------------------------------------------------------------------

} // namespace SimConnect

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
