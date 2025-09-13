// Copyright (c) 2025 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Event/Event.h>

// -----------------------------------------------------------------------------

class UIRequestAvailableCachesEvent
	: public Utils::SerialisableEvent
{
public:

	UIRequestAvailableCachesEvent() = default;

	UIRequestAvailableCachesEvent( const std::string& Locale )
		: Locale( Locale )
	{}

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override final
	{
		bool Success = true;

		Success &= Writer.WriteProperty( "locale", Locale );

		return Success;
	}

	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override final
	{
		bool Success = true;

		Success &= Reader.ReadProperty( "locale", Locale );

		return Success;
	}

public:

	std::string Locale;
};

// -----------------------------------------------------------------------------

template<>
struct Utils::SerialisableEventTraits< UIRequestAvailableCachesEvent >
{
	static constexpr char* Id = "SimCache.UIRequestAvailableCachesEvent";
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
