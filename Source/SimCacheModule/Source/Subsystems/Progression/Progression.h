// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include "Core/ProgressionData.h"

#include "Events/CacheFoundEvent.h"

#include <Utils/Event/NativeEventDispatcher.h>
#include <Utils/Optional/Optional.h>

#include <unordered_map>

// -----------------------------------------------------------------------------

namespace Subsystems
{

// -----------------------------------------------------------------------------

class Progression
{
public:

	Progression( Utils::NativeEventDispatcher& InternalEventDispatcher );

	bool Initialize();
	void Uninitialize();

	const Utils::DateTime* GetCacheAcquisitionTime( const CacheId& Id ) const;

private:

	void LoadProgressionData();
	bool SaveProgressionData();

	void RegisterCacheFoundListener();
	void UnregisterCacheFoundListener();
	void OnCacheFound( const CacheFoundEvent& Event );

private:

	Utils::NativeEventDispatcher& InternalEventDispatcher;

	Utils::EventHandle OnCacheFoundEventHandle;

	const std::string ProgressionPath;

	ProgressionData ProgressionData;

};

// -----------------------------------------------------------------------------

} // namespace Subsystems

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
