// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <chrono>
#include <string>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

class DateTime
{
public:

	DateTime();
	explicit DateTime( const std::chrono::system_clock::time_point& TimePoint );

	std::string ToISO8601UTC() const;

	static DateTime Now();
	static DateTime FromISO8601UTC( const std::string& DateTimeString );

private:

	std::chrono::system_clock::time_point TimePoint;
};

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
