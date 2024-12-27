// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/ViewModel.h"

// -----------------------------------------------------------------------------

ViewModel::ViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::WASMEventDispatcher& UIEventDispatcher )
	: InternalEventDispatcher( InternalEventDispatcher )
	, UIEventDispatcher( UIEventDispatcher )
{
}

// -----------------------------------------------------------------------------

ViewModel::~ViewModel()
{
}

// -----------------------------------------------------------------------------

bool ViewModel::Initialize()
{
	return true;
}

// -----------------------------------------------------------------------------

void ViewModel::Uninitialize()
{
}

// -----------------------------------------------------------------------------

Utils::NativeEventDispatcher& ViewModel::GetInternalEventDispatcher() const
{
	return InternalEventDispatcher;
}

// -----------------------------------------------------------------------------

Utils::WASMEventDispatcher& ViewModel::GetUIEventDispatcher() const
{
	return UIEventDispatcher;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
