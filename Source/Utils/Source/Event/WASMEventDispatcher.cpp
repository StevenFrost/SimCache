// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "WASMEventDispatcher.h"

#include <Utils/Enum/EnumUtils.h>
#include <Utils/WASM/Macros.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

WASMEventDispatcher::WASMEventDispatcher( const EWASMEventContext EventContext )
	: NextHandleId( 0 )
	, BroadcastFlags( EventContextToBroadcastFlags( EventContext ) )
	, RegisteredEvents()
{
}

// -----------------------------------------------------------------------------

WASMEventDispatcher::~WASMEventDispatcher()
{
	UnregisterAllEventListeners();
}

// -----------------------------------------------------------------------------

void WASMEventDispatcher::FireEvent( const std::string& EventId, const std::string& EventData )
{
	fsCommBusCall( EventId.c_str(), EventData.c_str(), EventData.size(), BroadcastFlags );
}

// -----------------------------------------------------------------------------

EventHandle WASMEventDispatcher::RegisterEventListener( const std::string& EventId, std::function< void( const std::string& ) >&& Callback )
{
	EventHandle Handle( NextHandleId++ );

	auto Context = std::make_shared< WASMEventContext >();
	Context->EventId = EventId;
	Context->Callback = Callback;

	RegisteredEvents.insert( std::make_pair( Handle, Context ) );

	fsCommBusRegister( EventId.c_str(), WASMEventDispatcher::ReceiveEvent, Context.get() );

	return Handle;
}

// -----------------------------------------------------------------------------

void WASMEventDispatcher::UnregisterEventListener( EventHandle& Handle )
{
	auto It = RegisteredEvents.find( Handle );
	if ( It != RegisteredEvents.end() )
	{
		fsCommBusUnregisterOneEvent( It->second->EventId.c_str(), WASMEventDispatcher::ReceiveEvent, It->second.get() );
		RegisteredEvents.erase( It );
	}

	Handle.Reset();
}

// -----------------------------------------------------------------------------

void WASMEventDispatcher::UnregisterAllEventListeners()
{
	for ( auto& RegisteredEvent : RegisteredEvents )
	{
		fsCommBusUnregisterOneEvent( RegisteredEvent.second->EventId.c_str(), WASMEventDispatcher::ReceiveEvent, RegisteredEvent.second.get() );
	}

	RegisteredEvents.clear();
}

// -----------------------------------------------------------------------------

FsCommBusBroadcastFlags WASMEventDispatcher::EventContextToBroadcastFlags( const EWASMEventContext EventContext ) const
{
	std::underlying_type< FsCommBusBroadcastFlags >::type Flags = 0;

	if ( HasFlag( EventContext, EWASMEventContext::JavaScript ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_JS;
	}
	if ( HasFlag( EventContext, EWASMEventContext::WASM ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_Wasm;
	}
	if ( HasFlag( EventContext, EWASMEventContext::Self ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_WasmSelfCall;
	}

	return static_cast< FsCommBusBroadcastFlags >( Flags );
}

// -----------------------------------------------------------------------------

void WASMEventDispatcher::ReceiveEvent( const char* Buffer, unsigned int BufferSize, void* Context )
{
	std::string Data( Buffer, BufferSize );
	reinterpret_cast< WASMEventContext* >( Context )->Callback( Data );
}

// -----------------------------------------------------------------------------

std::shared_ptr< EventDispatcher > MakeWASMEventDispatcher( const EWASMEventContext Context )
{
	return std::make_shared< WASMEventDispatcher >( Context );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
