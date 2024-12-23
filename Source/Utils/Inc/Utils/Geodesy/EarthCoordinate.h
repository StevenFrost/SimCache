// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Math/Vector3.h>
#include <Utils/Serialisation/Serialisable.h>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

class EarthCoordinate
	: public Serialisation::ISerialisable
{
public:

	// TODO: potentially remove default constructor
	// (currently only required for serialization to work with placeholder NativeEventDispatcher)
	EarthCoordinate() = default;

private:

	EarthCoordinate( const Vector3& GeocentricPosition );

public:

	static EarthCoordinate FromGeodetic( const double LatitudeDegrees, const double LongitudeDegrees, const double HeightAboveEllipsoidFeet );

	EarthCoordinate( const EarthCoordinate& Other ) = default;
	EarthCoordinate( EarthCoordinate&& Other ) = default;

	EarthCoordinate& operator=( const EarthCoordinate& Other ) = default;
	EarthCoordinate& operator=( EarthCoordinate&& Other ) = default;

	bool operator==( const EarthCoordinate& Other ) const;
	bool operator!=( const EarthCoordinate& Other ) const;

	EarthCoordinate operator+( const Vector3& RHS ) const;
	Vector3 operator-( const EarthCoordinate& RHS ) const;

	double DistanceTo( const EarthCoordinate& Other ) const;

public: // ISerialisable

	virtual bool Serialise( Utils::Serialisation::Writer& Writer ) const override;
	virtual bool Deserialise( Utils::Serialisation::Reader& Reader ) override;

public:

	Vector3 Geocentric;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
