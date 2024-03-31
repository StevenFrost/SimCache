// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/WASM/Macros.h>

#include <memory>
#include <string>

// -----------------------------------------------------------------------------

namespace SimConnect
{

// -----------------------------------------------------------------------------

class ISimConnectClient
{
public:

	virtual ~ISimConnectClient() = default;

	virtual bool Initialize() = 0;
	virtual bool Uninitialize() = 0;

	virtual bool IsConnected() const = 0;
};

// -----------------------------------------------------------------------------

std::shared_ptr< ISimConnectClient > MakeSimConnectClient( const std::string& ApplicationName );

// -----------------------------------------------------------------------------

} // namespace SimConnect

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
