// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <string>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

class ISerialisable
{
public:

	virtual std::string Serialise() const = 0;
	virtual void Deserialise( const std::string& Data ) = 0;

};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
