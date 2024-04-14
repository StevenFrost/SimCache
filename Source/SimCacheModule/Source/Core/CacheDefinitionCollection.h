// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Serialisation/Serialisable.h>
#include <Utils/Time/DateTime.h>

#include <cstdint>
#include <string>
#include <vector>

// -----------------------------------------------------------------------------

typedef std::string CacheId;
typedef std::string CacheAuthorId;
typedef std::string Locale;

// -----------------------------------------------------------------------------

struct CacheMetadata
	: public Utils::Serialisation::ISerialisable
{
	CacheMetadata();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	CacheId							Id;
	std::vector< CacheAuthorId >	Authors;
	Utils::DateTime					DatePlaced;

	uint8_t							Difficulty;
	std::string						SimObjectTitle;
};

// -----------------------------------------------------------------------------

struct CacheText
	: public Utils::Serialisation::ISerialisable
{
	CacheText();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	std::string Title;
	std::string Description;
	std::string Hint;
};

// -----------------------------------------------------------------------------

struct CacheLocText
	: public Utils::Serialisation::ISerialisable
{
	CacheLocText();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	std::string	Locale;
	CacheText	Text;
};

// -----------------------------------------------------------------------------

struct CachePosition
	: public Utils::Serialisation::ISerialisable
{
	CachePosition();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	double	Latitude;
	double	Longitude;

	double	Altitude;

	double	Pitch;
	double	Bank;
	double	Heading;

	bool	AltitudeIsAGL;
};

// -----------------------------------------------------------------------------

struct CacheTrackerSettings
	: public Utils::Serialisation::ISerialisable
{
	CacheTrackerSettings();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	float AlertDistance;
	float AcquireDistance;
};

// -----------------------------------------------------------------------------

struct CacheDefinition
	: public Utils::Serialisation::ISerialisable
{
	CacheDefinition();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	CacheMetadata				Metadata;
	std::vector< CacheLocText >	LocText;
	CachePosition				Position;
	CacheTrackerSettings		Tracker;
};

// -----------------------------------------------------------------------------

struct CacheAuthor
	: public Utils::Serialisation::ISerialisable
{
	CacheAuthor();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	CacheAuthorId	Id;
	std::string		Name;
};

// -----------------------------------------------------------------------------

class CacheDefinitionCollection
	: public Utils::Serialisation::ISerialisable
{
public:

	CacheDefinitionCollection();

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	std::string						Version;

	std::vector< CacheDefinition >	CacheDefinitions;
	std::vector< CacheAuthor >		Authors;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
