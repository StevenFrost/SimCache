// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Math/Vector3.h>

#include <cmath>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

Vector3::Vector3()
	: X( 0 )
	, Y( 0 )
	, Z( 0 )
{}

// -----------------------------------------------------------------------------

Vector3::Vector3( double X, double Y, double Z )
	: X( X )
	, Y( Y )
	, Z( Z )
{
}

// -----------------------------------------------------------------------------

bool Vector3::operator==( const Vector3& Other ) const
{
	return ( X == Other.X ) && ( Y == Other.Y ) && ( Z == Other.Z );
}

// -----------------------------------------------------------------------------

bool Vector3::operator!=( const Vector3& Other ) const
{
	return !( *this == Other );
}

// -----------------------------------------------------------------------------

double Vector3::Norm() const
{
	return sqrt( NormSquared() );
}

// -----------------------------------------------------------------------------

double Vector3::NormSquared() const
{
	return ( X * X ) + ( Y * Y ) + ( Z * Z );
}

// -----------------------------------------------------------------------------

double Vector3::Dot( const Vector3& RHS ) const
{
	return ( X * RHS.X ) + ( Y * RHS.Y ) + ( Z * RHS.Z );
}

// -----------------------------------------------------------------------------

Vector3 Vector3::Cross( const Vector3& RHS ) const
{
	return Vector3( ( Y * RHS.Z ) - ( Z * RHS.Y ), ( Z * RHS.X ) - ( X * RHS.Z ), ( X * RHS.Y ) - ( Y * RHS.X ) );
}

// -----------------------------------------------------------------------------

Vector3 Vector3::operator+( const Vector3& RHS ) const
{
	return Vector3( X + RHS.X, Y + RHS.Y, Z + RHS.Z );
}

// -----------------------------------------------------------------------------

Vector3 Vector3::operator-( const Vector3& RHS ) const
{
	return Vector3( X - RHS.X, Y - RHS.Y, Z - RHS.Z );
}

// -----------------------------------------------------------------------------

Vector3 Vector3::operator*( double c ) const
{
	return Vector3( X * c, Y * c, Z * c );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
