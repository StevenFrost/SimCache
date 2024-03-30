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

namespace WASMEventDispatcherPrivate
{

// -----------------------------------------------------------------------------

FsCommBusBroadcastFlags DispatcherTargetToBroadcastFlags( const EWASMEventDispatcherTarget Target )
{
	std::underlying_type< FsCommBusBroadcastFlags >::type Flags = 0;

	if ( HasFlag( Target, EWASMEventDispatcherTarget::JavaScript ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_JS;
	}
	if ( HasFlag( Target, EWASMEventDispatcherTarget::WASM ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_Wasm;
	}
	if ( HasFlag( Target, EWASMEventDispatcherTarget::Self ) )
	{
		Flags |= FsCommBusBroadcastFlags::FsCommBusBroadcast_WasmSelfCall;
	}

	return static_cast< FsCommBusBroadcastFlags >( Flags );
}

// -----------------------------------------------------------------------------

} // namespace WASMEventDispatcherPrivate

// -----------------------------------------------------------------------------

WASMEventDispatcher::WASMEventDispatcher( const EWASMEventDispatcherTarget Target )
	: BroadcastFlags( WASMEventDispatcherPrivate::DispatcherTargetToBroadcastFlags( Target ) )
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
	auto Handle = EventHandle::Make();

	auto Context = std::make_unique< WASMEventContext >();
	Context->EventId = EventId;
	Context->Callback = Callback;

	fsCommBusRegister( EventId.c_str(), WASMEventDispatcher::ReceiveEvent, Context.get() );

	RegisteredEvents.emplace( Handle, std::move( Context ) );

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

void WASMEventDispatcher::ReceiveEvent( const char* Buffer, unsigned int BufferSize, void* Context )
{
	std::string Data( Buffer, BufferSize );
	reinterpret_cast< WASMEventContext* >( Context )->Callback( Data );
}

// -----------------------------------------------------------------------------

std::shared_ptr< EventDispatcher > MakeWASMEventDispatcher( const EWASMEventDispatcherTarget Target )
{
	return std::make_shared< WASMEventDispatcher >( Target );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
