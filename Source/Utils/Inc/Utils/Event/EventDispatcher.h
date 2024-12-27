// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>
#include <Utils/Event/EventHandle.h>
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

template< EventIdSourceType EventIdSource = EventIdSourceType::TypeId >
class EventDispatcher
{
public:

	EventDispatcher() = default;
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

	template< class TEvent, EventIdSourceType IdSource = EventIdSource >
	auto GetEventId() const -> typename std::enable_if< ( IdSource == EventIdSourceType::EventTraits ), std::string >::type
	{
		return EventTraits< TEvent >::Id;
	}

	template< class TEvent, EventIdSourceType IdSource = EventIdSource >
	auto GetEventId() const -> typename std::enable_if< ( IdSource == EventIdSourceType::TypeId ), std::string >::type
	{
		return typeid( TEvent ).name();
	}
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
