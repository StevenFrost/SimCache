// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "NativeEventDispatcher.h"

#include <Utils/Logging/Log.h>

#include <memory>
#include <string>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( NativeEventDispatcher, Info )

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Internal
{

// -----------------------------------------------------------------------------

NativeEventDispatcher::NativeEventDispatcher()
	: EventDispatcher()
	, EventHandleToContextMap()
	, EventIdToHandlesMap()
{
}

// -----------------------------------------------------------------------------

void NativeEventDispatcher::FireEvent( const std::string& EventId, const Event& EventData )
{
	auto EventIdToHandlesIterator = EventIdToHandlesMap.find( EventId );
	if ( EventIdToHandlesIterator == EventIdToHandlesMap.end() )
	{
		return;
	}

	for ( auto& EventHandle : EventIdToHandlesIterator->second )
	{
		auto EventHandleToContextIterator = EventHandleToContextMap.find( EventHandle );
		if ( EventHandleToContextIterator == EventHandleToContextMap.end() )
		{
			continue;
		}

		EventHandleToContextIterator->second->EventHandler( EventData );
	}
}

// -----------------------------------------------------------------------------

EventHandle NativeEventDispatcher::RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler )
{
	auto Handle = EventHandle::Make();

	auto Context = std::make_unique< NativeEventContext >();
	Context->EventId = EventId;
	Context->EventHandler = EventHandler;

	EventHandleToContextMap.emplace( Handle, std::move( Context ) );

	auto Iterator = EventIdToHandlesMap.find( EventId );
	if ( Iterator == EventIdToHandlesMap.end() )
	{
		EventIdToHandlesMap.emplace( EventId, std::vector< EventHandle >{ Handle } );
	}
	else
	{
		Iterator->second.push_back( Handle );
	}

	return Handle;
}

// -----------------------------------------------------------------------------

void NativeEventDispatcher::UnregisterEventListener( EventHandle& Handle )
{
	auto EventHandleToContextIterator = EventHandleToContextMap.find( Handle );
	if ( EventHandleToContextIterator != EventHandleToContextMap.end() )
	{
		const auto EventId = EventHandleToContextIterator->second->EventId;

		auto EventIdToHandlesIterator = EventIdToHandlesMap.find( EventId );
		if ( EventIdToHandlesIterator != EventIdToHandlesMap.end() )
		{
			EventIdToHandlesMap.erase( EventIdToHandlesIterator );
		}

		EventHandleToContextMap.erase( EventHandleToContextIterator );
	}

	Handle.Reset();
}

// -----------------------------------------------------------------------------

} // namespace Internal

// -----------------------------------------------------------------------------

std::unique_ptr< NativeEventDispatcher > MakeNativeEventDispatcher()
{
	return std::make_unique< Internal::NativeEventDispatcher >();
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
