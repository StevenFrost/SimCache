// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Time/DateTime.h>

#include <iomanip>
#include <sstream>

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

namespace DateTimePrivate
{
	static const char* ISO8601Format = "%FT%T";
} // namespace DateTimePrivate

// -----------------------------------------------------------------------------

DateTime::DateTime()
	: TimePoint()
{
}

// -----------------------------------------------------------------------------

DateTime::DateTime( const std::chrono::system_clock::time_point& TimePoint )
	: TimePoint( TimePoint )
{
}

// -----------------------------------------------------------------------------

std::string DateTime::ToISO8601UTC() const
{
	const auto SecondsSinceEpoch = std::chrono::system_clock::to_time_t( TimePoint );
	const auto* TimeComponents = gmtime( &SecondsSinceEpoch );

	std::stringstream StringStream;
	StringStream << std::put_time( TimeComponents, DateTimePrivate::ISO8601Format );

	const auto TruncatedTime = std::chrono::system_clock::from_time_t( SecondsSinceEpoch );
	const auto Milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( TimePoint - TruncatedTime ).count();

	StringStream << "." << std::fixed << std::setw( 3 ) << std::setfill( '0' ) << Milliseconds << "Z";

	return StringStream.str();
}

// -----------------------------------------------------------------------------

DateTime DateTime::Now()
{
	return DateTime( std::chrono::system_clock::now() );
}

// -----------------------------------------------------------------------------

DateTime DateTime::FromISO8601UTC( const std::string& DateTimeString )
{
	std::istringstream StringStream( DateTimeString );
	std::tm TimeComponents = {};

	std::string Tail;
	StringStream >> std::get_time( &TimeComponents, DateTimePrivate::ISO8601Format ) >> Tail;

	const auto SecondsSinceEpoch = std::mktime( &TimeComponents );
	auto TimePoint = std::chrono::system_clock::from_time_t( SecondsSinceEpoch );

	if ( Tail.size() == 5 && Tail[ 0 ] == '.' && Tail[ 4 ] == 'Z' )
	{
		const auto MillisecondsString = Tail.substr( 1, 3 );
		const auto Milliseconds = std::atoi( MillisecondsString.c_str() );

		TimePoint += std::chrono::milliseconds( Milliseconds );
	}

	return DateTime( TimePoint );
}

// -----------------------------------------------------------------------------

} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
