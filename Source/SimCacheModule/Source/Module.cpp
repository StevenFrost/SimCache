// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "Module/SimCacheModule.h"

#include <MSFS/MSFS.h>
#include <Utils/WASM/Macros.h>

#include <memory>

// -----------------------------------------------------------------------------

static std::unique_ptr< SimCacheModule > Module = nullptr;

// -----------------------------------------------------------------------------

extern "C" MSFS_CALLBACK void module_init()
{
	Module = std::make_unique< SimCacheModule >();

	const bool InitializeSucceeded = Module->Initialize();
	if ( !InitializeSucceeded )
	{
		Module->Uninitialize();
		Module = nullptr;

		return;
	}
}

// -----------------------------------------------------------------------------

extern "C" MSFS_CALLBACK void module_deinit()
{
	if ( !Module )
	{
		return;
	}

	Module->Uninitialize();
	Module = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
