// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Event/EventHandle.h>
#include <Utils/Serialisation/JSON/JSONReader.h>
#include <Utils/Serialisation/JSON/JSONWriter.h>
#include <Utils/WASM/Macros.h>

#include <functional>
#include <memory>
#include <string>
#include <type_traits>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

enum class EventIdSourceType
{
	TypeId,
	EventTraits
};

// -----------------------------------------------------------------------------

class EventDispatcher
{
public:

	EventDispatcher( const EventIdSourceType EventIdSource )
		: EventIdSource( EventIdSource )
	{}

	virtual ~EventDispatcher() = default;

	template< class TEvent >
	void FireEvent( const TEvent& Event )
	{
		static_assert( std::is_base_of< Utils::Event, TEvent >::value, "TEvent must be derived from Event" );

		FireEvent( GetEventId< TEvent >(), Event );
	}

	template< class TEvent >
	EventHandle RegisterEventListener( std::function< void( const TEvent& ) >&& Callback )
	{
		static_assert( std::is_default_constructible< TEvent >::value, "TEvent must be default constructible" );
		static_assert( std::is_base_of< Utils::Event, TEvent >::value, "TEvent must be derived from Event" );

		return RegisterEventListener( GetEventId< TEvent >(),
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

	virtual void UnregisterEventListener( EventHandle& Handle ) = 0;

private:

	virtual void FireEvent( const std::string& EventId, const Event& EventData ) = 0;
	virtual EventHandle RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler ) = 0;

	template< class TEvent >
	std::string GetEventId() const
	{
		switch ( EventIdSource )
		{
		case EventIdSourceType::EventTraits:
			return EventTraits< TEvent >::Id;
		case EventIdSourceType::TypeId:
		default:
			return typeid( TEvent ).name();
		}
	}

private:

	const EventIdSourceType EventIdSource;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
