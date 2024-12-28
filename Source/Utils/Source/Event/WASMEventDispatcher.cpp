// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "WASMEventDispatcher.h"

#include <Utils/Enum/EnumUtils.h>
#include <Utils/Logging/Log.h>
#include <Utils/Serialisation/JSON/JSONReader.h>
#include <Utils/Serialisation/JSON/JSONWriter.h>
#include <Utils/Serialisation/Serialisable.h>
#include <Utils/WASM/Macros.h>

#include <memory>
#include <string>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( WASMEventDispatcher, Info )

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Internal
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
	: EventDispatcher()
	, BroadcastFlags( WASMEventDispatcherPrivate::DispatcherTargetToBroadcastFlags( Target ) )
	, RegisteredEvents()
{
}

// -----------------------------------------------------------------------------

WASMEventDispatcher::~WASMEventDispatcher()
{
	UnregisterAllEventListeners();
}

// -----------------------------------------------------------------------------

void WASMEventDispatcher::FireEvent( const std::string& EventId, const Event& EventData )
{
	const auto* SerialisableEvent = dynamic_cast< const Serialisation::ISerialisable* >( &EventData );
	if ( !SerialisableEvent )
	{
		LOG( WASMEventDispatcher, Error, "Event %s does not implement ISerialisable", EventId.c_str() );
		return;
	}

	Utils::Serialisation::JSONWriter Writer;
	SerialisableEvent->Serialise( Writer );

	const auto SerialisedEvent = Writer.ToString();
	fsCommBusCall( EventId.c_str(), SerialisedEvent.c_str(), SerialisedEvent.size(), BroadcastFlags );
}

// -----------------------------------------------------------------------------

EventHandle WASMEventDispatcher::RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler )
{
	auto Handle = EventHandle::Make();

	auto Context = std::make_unique< WASMEventContext >();
	Context->EventId = EventId;
	Context->EventBuilder = EventBuilder;
	Context->EventHandler = EventHandler;

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
	auto* EventContext = reinterpret_cast< WASMEventContext* >( Context );
	if ( !EventContext )
	{
		LOG( WASMEventDispatcher, Error, "Invalid event context" );
		return;
	}

	auto EventInstance = EventContext->EventBuilder();
	if ( !EventInstance )
	{
		LOG( WASMEventDispatcher, Error, "Failed to create event instance" );
		return;
	}

	auto* SerialisableEvent = dynamic_cast< Serialisation::ISerialisable* >( EventInstance.get() );
	if ( !SerialisableEvent )
	{
		LOG( WASMEventDispatcher, Error, "Event instance does not implement ISerialisable" );
		return;
	}

	std::string Data( Buffer, BufferSize );
	if ( Data.empty() )
	{
		LOG( WASMEventDispatcher, Error, "Invalid event data" );
		return;
	}

	Utils::Serialisation::JSONReader Reader( Data );
	SerialisableEvent->Deserialise( Reader );

	EventContext->EventHandler( *EventInstance.get() );
}

// -----------------------------------------------------------------------------

} // namespace Internal

// -----------------------------------------------------------------------------

std::unique_ptr< WASMEventDispatcher > MakeWASMEventDispatcher( const EWASMEventDispatcherTarget Target )
{
	return std::make_unique< Internal::WASMEventDispatcher >( Target );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
