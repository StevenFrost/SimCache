// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Event/EventHandle.h>
#include <Utils/WASM/Macros.h>

#include <functional>
#include <string>
#include <type_traits>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

template< class TEventHandler >
class EventDispatcher
{
public:

	EventDispatcher() = default;
	virtual ~EventDispatcher() = default;

	template< class TEvent >
	void FireEvent( const TEvent& Event )
	{
		static_assert( std::is_base_of< Utils::Event, TEvent >::value, "TEvent must be derived from Event" );
		TEventHandler::FireEvent( *this, Event );
	}

	template< class TEvent >
	EventHandle RegisterEventListener( std::function< void( const TEvent& ) >&& Callback )
	{
		static_assert( std::is_base_of< Utils::Event, TEvent >::value, "TEvent must be derived from Event" );
		return TEventHandler::template RegisterEventListener< TEvent >( *this, std::move( Callback ) );
	}

	virtual void UnregisterEventListener( EventHandle& Handle ) = 0;

private:

	virtual void FireEvent( const std::string& EventId, const Event& EventData ) = 0;
	virtual EventHandle RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler ) = 0;

	friend TEventHandler;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
