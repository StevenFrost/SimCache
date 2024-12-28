// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>
#include <Utils/Event/NativeEventDispatcher.h>
#include <Utils/WASM/Macros.h>

#include <memory>
#include <unordered_map>
#include <vector>

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Internal
{

// -----------------------------------------------------------------------------

struct NativeEventContext
{
	NativeEventContext() = default;

	std::string								EventId;
	std::function< void( const Event& ) >	EventHandler;
};

// -----------------------------------------------------------------------------

class NativeEventDispatcher
	: public EventDispatcher< NativeEventHandler >
{
public:

	NativeEventDispatcher();
	virtual ~NativeEventDispatcher() = default;

private:

	virtual void FireEvent( const std::string& EventId, const Event& EventData ) override final;

	virtual EventHandle RegisterEventListener( const std::string& EventId, std::function< std::unique_ptr< Event >() >&& EventBuilder, std::function< void( const Event& ) >&& EventHandler ) override final;
	virtual void UnregisterEventListener( EventHandle& Handle ) override final;

private:

	typedef std::unordered_map< EventHandle, std::unique_ptr< NativeEventContext >, HandleHasher > EventHandleToContextMapType;
	typedef std::unordered_map< std::string, std::vector< EventHandle > > EventIdToHandlesMapType;

	EventHandleToContextMapType	EventHandleToContextMap;
	EventIdToHandlesMapType EventIdToHandlesMap;
};

// -----------------------------------------------------------------------------

} // namespace Internal
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
