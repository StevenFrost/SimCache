// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Event/EventHandle.h>

#include <cstdint>
#include <utility>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

const int32_t EventHandle::InvalidId = -1;
int32_t EventHandle::NextId = 0;

// -----------------------------------------------------------------------------

EventHandle EventHandle::Make()
{
	return EventHandle( NextId++ );
}

// -----------------------------------------------------------------------------

EventHandle::EventHandle()
	: Id( InvalidId )
{}

// -----------------------------------------------------------------------------

EventHandle::EventHandle( const int32_t Id )
	: Id( Id )
{}

// -----------------------------------------------------------------------------

bool EventHandle::operator==( const EventHandle& Other ) const
{
	return Id == Other.Id;
}

// -----------------------------------------------------------------------------

bool EventHandle::operator!=( const EventHandle& Other ) const
{
	return !( *this == Other );
}

// -----------------------------------------------------------------------------

bool EventHandle::IsValid() const
{
	return Id != InvalidId;
}

// -----------------------------------------------------------------------------

void EventHandle::Reset()
{
	Id = InvalidId;
}

// -----------------------------------------------------------------------------

size_t EventHandleHasher::operator()( const EventHandle& Handle ) const
{
	return std::hash< int32_t >()( Handle.Id );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
