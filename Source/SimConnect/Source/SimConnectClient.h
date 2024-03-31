// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <MSFS/MSFS_WindowsTypes.h>
#include <SimConnect/SimConnectClient.h>

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

	virtual bool Initialize() override final;
	virtual bool Uninitialize() override final;

	virtual bool IsConnected() const override final;

private:

	bool OpenConnection();
	bool CloseConnection();

private:

	const std::string	ApplicationName;

	HANDLE				SimConnectHandle;

};

// -----------------------------------------------------------------------------

} // namespace SimConnect

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
