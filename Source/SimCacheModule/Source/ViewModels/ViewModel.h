// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/NativeEventDispatcher.h>
#include <Utils/Event/WASMEventDispatcher.h>

// -----------------------------------------------------------------------------

class ViewModel
{
public:

	ViewModel(
		Utils::NativeEventDispatcher& InternalEventDispatcher,
		Utils::WASMEventDispatcher& UIEventDispatcher
	);

	virtual ~ViewModel();

	virtual bool Initialize();
	virtual void Uninitialize();

protected:

	Utils::NativeEventDispatcher& GetInternalEventDispatcher() const;
	Utils::WASMEventDispatcher& GetUIEventDispatcher() const;

private:

	Utils::NativeEventDispatcher&	InternalEventDispatcher;
	Utils::WASMEventDispatcher&		UIEventDispatcher;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
