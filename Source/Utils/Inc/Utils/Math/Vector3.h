// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

struct Vector3
{
public:

	Vector3();
	Vector3( const double X, const double Y, const double Z );

	Vector3( const Vector3& Other ) = default;
	Vector3( Vector3&& Other ) = default;

	Vector3& operator=( const Vector3& Other ) = default;
	Vector3& operator=( Vector3&& Other ) = default;

	bool operator==( const Vector3& Other ) const;
	bool operator!=( const Vector3& Other ) const;

	double Norm() const;
	double NormSquared() const;

	double Dot( const Vector3& RHS ) const;
	Vector3 Cross( const Vector3& RHS ) const;

	Vector3 operator+( const Vector3& RHS ) const;
	Vector3 operator-( const Vector3& RHS ) const;
	Vector3 operator*( double c ) const;

public:

	double X;
	double Y;
	double Z;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
