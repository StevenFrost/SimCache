// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "SimConnectClient.h"

#include <SimConnect.h>

// -----------------------------------------------------------------------------

namespace SimConnect
{

// -----------------------------------------------------------------------------

SimConnectClient::SimConnectClient( const std::string& ApplicationName )
	: ApplicationName( ApplicationName )
	, SimConnectHandle( INVALID_HANDLE_VALUE )
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

bool SimConnectClient::OpenConnection()
{
	if ( SimConnect_Open( &SimConnectHandle, ApplicationName.c_str(), nullptr, 0, 0, 0 ) != S_OK )
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool SimConnectClient::CloseConnection()
{
	if ( SimConnect_Close( SimConnectHandle ) != S_OK )
	{
		return false;
	}

	SimConnectHandle = INVALID_HANDLE_VALUE;

	return true;
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
