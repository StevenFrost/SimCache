// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/EventDispatcher.h>

#include <memory>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

enum class EWASMEventDispatcherTarget : int8_t
{
	JavaScript = 0x1,
	WASM = 0x2,
	Self = 0x4 | WASM,
	JavaScriptAndWASM = JavaScript | WASM,
	All = JavaScript | WASM | Self
};

// -----------------------------------------------------------------------------

std::shared_ptr< EventDispatcher > MakeWASMEventDispatcher( const EWASMEventDispatcherTarget Target );

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
