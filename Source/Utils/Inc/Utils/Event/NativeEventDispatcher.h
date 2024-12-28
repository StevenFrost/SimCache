// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>

#include <memory>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

struct NativeEventHandler
{
	template< class TEvent >
	static void FireEvent( EventDispatcher< NativeEventHandler >& Dispatcher, const TEvent& Event )
	{
		Dispatcher.FireEvent( GetEventId< TEvent >(), Event );
	}

	template< class TEvent >
	static EventHandle RegisterEventListener( EventDispatcher< NativeEventHandler >& Dispatcher, std::function< void( const TEvent& ) >&& Callback )
	{
		return Dispatcher.RegisterEventListener( GetEventId< TEvent >(), nullptr,
			[ Callback ]( const Event& EventData )
			{
				Callback( *dynamic_cast< const TEvent* >( &EventData ) );
			}
		);
	}

	template< class TEvent >
	static std::string GetEventId()
	{
		return typeid( TEvent ).name();
	}
};

// -----------------------------------------------------------------------------

typedef EventDispatcher< NativeEventHandler > NativeEventDispatcher;

// -----------------------------------------------------------------------------

std::unique_ptr< NativeEventDispatcher > MakeNativeEventDispatcher();

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
