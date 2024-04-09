// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Serialisation/Reader.h>
#include <Utils/Serialisation/Writer.h>

#include <string>

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

class ISerialisable
{
public:

	virtual ~ISerialisable() = default;

	virtual bool Serialise( Writer& Writer ) const = 0;
	virtual bool Deserialise( Reader& Reader ) = 0;

};

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
