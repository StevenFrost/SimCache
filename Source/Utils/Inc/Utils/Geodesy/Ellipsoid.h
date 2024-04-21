// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

struct WGS84EllipsoidParams
{
	static constexpr double a = 6378137.0; // semi-major axis (a)
	static constexpr double f = 1.0 / 298.257223563; // flattening (f)
};

// -----------------------------------------------------------------------------

template< class TEllipsoidParams >
struct Ellipsoid
{
	static constexpr double a = TEllipsoidParams::a; // semi-major axis (a)
	static constexpr double f = TEllipsoidParams::f; // flattening (f)
	static constexpr double b = a * ( 1.0 - f ); // semi-minor axis (b)
	static constexpr double eSquared = ( 2.0 - f ) * f; // first eccentricity squared (e^2)
	static constexpr double ePrimeSquared = ( ( a * a ) / ( b * b ) ) - 1.0; // second eccentricity squared (e'^2)
};

// -----------------------------------------------------------------------------

typedef Ellipsoid< WGS84EllipsoidParams > WGS84Ellipsoid;

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
