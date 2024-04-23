// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/ViewModel.h"

// -----------------------------------------------------------------------------

ViewModel::ViewModel( Utils::NativeEventDispatcher& InternalEventDispatcher, Utils::EventDispatcher& ViewEventDispatcher )
	: InternalEventDispatcher( InternalEventDispatcher )
	, ViewEventDispatcher( ViewEventDispatcher )
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

Utils::EventDispatcher& ViewModel::GetViewEventDispatcher() const
{
	return ViewEventDispatcher;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
