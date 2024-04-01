// Copyright (c) 2024 Steven Frost and Orion Lyau

#include "ViewModels/ViewModel.h"

// -----------------------------------------------------------------------------

ViewModel::ViewModel( Utils::EventDispatcher& ViewEventDispatcher )
	: ViewEventDispatcher( ViewEventDispatcher )
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

Utils::EventDispatcher& ViewModel::GetViewEventDispatcher() const
{
	return ViewEventDispatcher;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
