// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <MSFS/MSFS_CommBus.h>
#include <Utils/Event/EventDispatcher.h>
#include <Utils/Event/WASMEventDispatcher.h>
#include <Utils/WASM/Macros.h>

#include <memory>
#include <unordered_map>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

struct WASMEventContext
{
	WASMEventContext() = default;

	std::string										EventId;
	std::function< std::unique_ptr< Event >() >		EventBuilder;
	std::function< void( const Event& ) >			EventHandler;
};

// -----------------------------------------------------------------------------

class WASMEventDispatcher
	: public EventDispatcher
{
public:

	WASMEventDispatcher( const EventIdSourceType EventIdSource, const EWASMEventDispatcherTarget Target );
	virtual ~WASMEventDispatcher();

private:

	virtual void FireEvent( const std::string& EventId, const Event& EventData ) override final;

	virtual EventHandle RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler ) override final;
	virtual void UnregisterEventListener( EventHandle& Handle ) override final;

private:

	void UnregisterAllEventListeners();

	static void ReceiveEvent( const char* Buffer, unsigned int BufferSize, void* Context );

private:

	typedef std::unordered_map< EventHandle, std::unique_ptr< WASMEventContext >, HandleHasher > EventContextMap;

	FsCommBusBroadcastFlags	BroadcastFlags;
	EventContextMap			RegisteredEvents;

};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
