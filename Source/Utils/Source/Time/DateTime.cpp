// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Time/DateTime.h>

#include <Utils/Logging/Log.h>

#include <iomanip>
#include <sstream>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( DateTime, Info )

// -----------------------------------------------------------------------------

namespace Utils
{

// -----------------------------------------------------------------------------

namespace DateTimePrivate
{
	static constexpr char* ISO8601Format = "%FT%T";
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

std::string DateTime::ToISO8601UTC( const bool IncludeMilliseconds ) const
{
	const auto SecondsSinceEpoch = std::chrono::system_clock::to_time_t( TimePoint );
	const auto* TimeComponents = gmtime( &SecondsSinceEpoch );

	std::stringstream StringStream;
	StringStream << std::put_time( TimeComponents, DateTimePrivate::ISO8601Format );

	if ( IncludeMilliseconds )
	{
		const auto TruncatedTime = std::chrono::system_clock::from_time_t( SecondsSinceEpoch );
		const auto Milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( TimePoint - TruncatedTime ).count();

		StringStream << "." << std::fixed << std::setw( 3 ) << std::setfill( '0' ) << Milliseconds;
	}

	StringStream << "Z";

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
	if ( DateTimeString[ DateTimeString.size() - 1 ] != 'Z' )
	{
		LOG( DateTime, Error, "FromISO8601UTC called with a non-UTC date time string" );
		return DateTime();
	}

	std::istringstream StringStream( DateTimeString );
	std::tm TimeComponents = {};

	std::string Tail;
	StringStream >> std::get_time( &TimeComponents, DateTimePrivate::ISO8601Format ) >> Tail;

	const auto SecondsSinceEpoch = std::mktime( &TimeComponents );
	auto TimePoint = std::chrono::system_clock::from_time_t( SecondsSinceEpoch );

	if ( Tail[ 0 ] == '.' )
	{
		const auto MillisecondsString = Tail.substr( 1, Tail.size() - 2 );
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
