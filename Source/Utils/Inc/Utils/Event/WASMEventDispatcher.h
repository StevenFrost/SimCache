// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>

#include <memory>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

enum class EWASMEventDispatcherTarget : int8_t
{
	JavaScript = 0x1,
	WASM = 0x2,
	Self = 0x4 | WASM,
	JavaScriptAndWASM = JavaScript | WASM,
	All = JavaScript | WASM | Self
};

// -----------------------------------------------------------------------------

struct WASMEventHandler
{
	template< class TEvent >
	static void FireEvent( EventDispatcher< WASMEventHandler >& Dispatcher, const TEvent& Event )
	{
		Dispatcher.FireEvent( GetEventId< TEvent >(), Event );
	}

	template< class TEvent >
	static EventHandle RegisterEventListener( EventDispatcher< WASMEventHandler >& Dispatcher, std::function< void( const TEvent& ) >&& Callback )
	{
		static_assert( std::is_default_constructible< TEvent >::value, "TEvent must be default constructible" );

		return Dispatcher.RegisterEventListener( GetEventId< TEvent >(),
			[]()
			{
				return std::make_unique< TEvent >();
			},
			[ Callback ]( const Event& EventData )
			{
				Callback( *dynamic_cast< const TEvent* >( &EventData ) );
			}
		);
	}

	template< class TEvent >
	static std::string GetEventId()
	{
		return EventTraits< TEvent >::Id;
	}
};

// -----------------------------------------------------------------------------

typedef EventDispatcher< WASMEventHandler > WASMEventDispatcher;

// -----------------------------------------------------------------------------

std::shared_ptr< WASMEventDispatcher > MakeWASMEventDispatcher( const EWASMEventDispatcherTarget Target );

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
