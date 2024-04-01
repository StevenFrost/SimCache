// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>

// -----------------------------------------------------------------------------

class ViewModel
{
public:

	ViewModel( Utils::EventDispatcher& ViewEventDispatcher );

	virtual ~ViewModel();

	virtual bool Initialize();
	virtual void Uninitialize();

protected:

	Utils::EventDispatcher& GetViewEventDispatcher() const;

private:

	Utils::EventDispatcher& ViewEventDispatcher;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
