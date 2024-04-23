// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>

// -----------------------------------------------------------------------------

namespace Utils
{
	typedef EventDispatcher NativeEventDispatcher;
}

// -----------------------------------------------------------------------------

class ViewModel
{
public:

	ViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher );

	virtual ~ViewModel();

	virtual bool Initialize();
	virtual void Uninitialize();

protected:

	Utils::NativeEventDispatcher& GetInternalEventDispatcher() const;
	Utils::EventDispatcher& GetViewEventDispatcher() const;

private:

	Utils::NativeEventDispatcher& InternalEventDispatcher;
	Utils::EventDispatcher& ViewEventDispatcher;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
