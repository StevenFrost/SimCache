// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Geodesy/EarthCoordinate.h>

#include <Utils/Geodesy/Ellipsoid.h>

#include <cmath>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

namespace EarthCoordinatePrivate
{
	static constexpr double DegreesToRadians = M_PI / 180.0;
	static constexpr double FeetToMeters = 0.3048;
} // namespace EarthCoordinatePrivate

// -----------------------------------------------------------------------------

EarthCoordinate::EarthCoordinate( const Vector3& GeocentricPosition )
	: Geocentric( GeocentricPosition )
{
}

// -----------------------------------------------------------------------------

EarthCoordinate EarthCoordinate::FromGeodetic( const double LatitudeDegrees, const double LongitudeDegrees, const double HeightAboveEllipsoidFeet )
{
	const auto phi = LatitudeDegrees * EarthCoordinatePrivate::DegreesToRadians;
	const auto lambda = LongitudeDegrees * EarthCoordinatePrivate::DegreesToRadians;
	const auto h = HeightAboveEllipsoidFeet * EarthCoordinatePrivate::FeetToMeters;
	const auto sp = sin( phi );
	const auto N = Utils::WGS84Ellipsoid::a / sqrt( 1.0 - ( Utils::WGS84Ellipsoid::eSquared * sp * sp ) );
	const auto r = ( N + h ) * cos( phi );
	const auto GeocentricPosition = Vector3(
		r * cos( lambda ),
		r * sin( lambda ),
		( ( ( 1.0 - Utils::WGS84Ellipsoid::eSquared ) * N ) + h ) * sp
	);
	return EarthCoordinate( GeocentricPosition );
}

// -----------------------------------------------------------------------------

bool EarthCoordinate::operator==( const EarthCoordinate& Other ) const
{
	return Geocentric == Other.Geocentric;
}

// -----------------------------------------------------------------------------

bool EarthCoordinate::operator!=( const EarthCoordinate& Other ) const
{
	return Geocentric != Other.Geocentric;
}

// -----------------------------------------------------------------------------

EarthCoordinate EarthCoordinate::operator+( const Vector3& RHS ) const
{
	return EarthCoordinate( Geocentric + RHS );
}

// -----------------------------------------------------------------------------

Vector3 EarthCoordinate::operator-( const EarthCoordinate& RHS ) const
{
	return Geocentric - RHS.Geocentric;
}

// -----------------------------------------------------------------------------

double EarthCoordinate::DistanceTo( const EarthCoordinate& Other ) const
{
	return ( Other - *this ).Norm();
}

// -----------------------------------------------------------------------------

bool EarthCoordinate::Serialise( Utils::Serialisation::Writer& Writer ) const
{
	return Writer.WriteProperty( "Geocentric", Geocentric );
}

// -----------------------------------------------------------------------------

bool EarthCoordinate::Deserialise( Utils::Serialisation::Reader& Reader )
{
	return Reader.ReadProperty( "Geocentric", Geocentric );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
