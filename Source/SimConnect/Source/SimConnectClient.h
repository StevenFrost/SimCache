// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <SimConnect/SimConnectClient.h>

#include <Utils/Handle/Handle.h>

#include <MSFS/MSFS_WindowsTypes.h>
#include <SimConnect.h>

#include <unordered_map>

// -----------------------------------------------------------------------------

namespace SimConnect
{

// -----------------------------------------------------------------------------

class SimConnectClient
	: public ISimConnectClient
{
public:

	SimConnectClient( const std::string& ApplicationName );
	virtual ~SimConnectClient();

	SimConnectClient( const SimConnectClient& Other ) = delete;
	SimConnectClient( SimConnectClient&& Other ) = delete;

	SimConnectClient& operator=( const SimConnectClient& Other ) = delete;
	SimConnectClient& operator=( SimConnectClient&& Other ) = delete;

public: // ISimConnectClient

	virtual bool Initialize() override final;
	virtual bool Uninitialize() override final;

	virtual bool IsConnected() const override final;

	virtual SimConnect::Handle StartReceivingUserAircraftPositionUpdates( UserAircraftPositionUpdateFunc&& OnUserAircraftPositionUpdated ) override final;
	virtual bool StopReceivingUserAircraftPositionUpdates( SimConnect::Handle& Handle ) override final;

	virtual SimConnect::Handle CreateSimObject( const std::string& SimObjectTitle, const SimObjectPosition& Position, SimObjectCreatedFunc&& OnSimObjectCreated ) override final;
	virtual bool DestroySimObject( SimConnect::Handle& Handle ) override final;

private:

	bool OpenConnection();
	bool CloseConnection();

	bool RegisterCallbacks();

	bool BuildDataDefinitions();
	bool BuildAircraftPositionDataDefinition();

	void OnConnectionOpen( const SIMCONNECT_RECV_OPEN& Data );
	void OnSimObjectAssignedId( const SIMCONNECT_RECV_ASSIGNED_OBJECT_ID& Data );
	void OnReceivedSimObjectData( const SIMCONNECT_RECV_SIMOBJECT_DATA& Data );

private:

	static void CALLBACK DispatchProc( SIMCONNECT_RECV* Data, DWORD DataSizeBytes, void* Context );

private:

	template< class THandle, class TValue >
	using THandleMap = std::unordered_map< THandle, TValue, Utils::HandleHasher >;

	const std::string										ApplicationName;
	HANDLE													SimConnectHandle;

	THandleMap< Handle, UserAircraftPositionUpdateFunc >	UserAircraftPositionUpdateRegistry;

	THandleMap< Handle, SimObjectCreatedFunc >				SimObjectsPendingCreation;
	THandleMap< Handle, SIMCONNECT_OBJECT_ID >				CreatedSimObjects;

};

// -----------------------------------------------------------------------------

} // namespace SimConnect

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
