// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Logging/Log.h>

#include <chrono>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>

// -----------------------------------------------------------------------------

#ifdef LOGGING_ENABLED

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Logging
{

// -----------------------------------------------------------------------------

std::string GetTimestampString()
{
	const auto CurrentTime = std::chrono::system_clock::now();
	const auto SecondsSinceEpoch = std::chrono::system_clock::to_time_t( CurrentTime );
	const auto* TimeComponents = gmtime( &SecondsSinceEpoch );

	std::stringstream StringStream;
	StringStream << std::put_time( TimeComponents, "%FT%T" );

	const auto TruncatedTime = std::chrono::system_clock::from_time_t( SecondsSinceEpoch );
	const auto Milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( CurrentTime - TruncatedTime ).count();

	StringStream << "." << std::fixed << std::setw( 3 ) << std::setfill( '0' ) << Milliseconds << "Z";

	return StringStream.str();
}

// -----------------------------------------------------------------------------

std::string GetLevelString( const Logging::Level Level )
{
	switch ( Level )
	{
	case Logging::Level::Error:
		return "Error";
	case Logging::Level::Warning:
		return "Warning";
	case Logging::Level::Info:
		return "Info";
	case Logging::Level::Verbose:
		return "Verbose";
	default:
		return "Unknown";
	};
}

// -----------------------------------------------------------------------------

Category::Category( const std::string& CategoryName, const Level CategoryLevel )
	: CategoryName( CategoryName )
	, CategoryLevel( CategoryLevel == Level::Default ? Level::Info : CategoryLevel )
{
}

// -----------------------------------------------------------------------------

void Category::Output( Level LogLevel, std::string LogMessage, ... )
{
	typedef std::underlying_type< Level >::type LevelType;

	const auto RequestedLevel = static_cast< LevelType >( LogLevel );
	const auto MaximumLevel = static_cast< LevelType >( CategoryLevel );

	if ( RequestedLevel > MaximumLevel )
	{
		return;
	}

	va_list Args;

	va_start( Args, LogMessage );
	OutputInternal( LogLevel, LogMessage, Args );
	va_end( Args );
}

// -----------------------------------------------------------------------------

void Category::OutputInternal( Logging::Level Level, std::string const& Message, va_list Args )
{
	va_list ArgsCopy;
	va_copy( ArgsCopy, Args );

	const auto ArgsLength = vsnprintf( 0, 0, Message.c_str(), ArgsCopy );

	std::string FormattedMessage;
	FormattedMessage.resize( ArgsLength + 1 );
	vsnprintf( &FormattedMessage[ 0 ], ArgsLength + 1, Message.c_str(), Args );
	FormattedMessage.resize( ArgsLength );

	// [ISO-8601 DateTime UTC][SolutionName][CategoryName][Level] Message
	std::stringstream StringStream;
	StringStream << "[" << GetTimestampString() << "]";
	StringStream << "[" << SOLUTION_NAME << "]";
	StringStream << "[" << CategoryName << "]";
	StringStream << "[" << GetLevelString( Level ) << "]";
	StringStream << " " << FormattedMessage;

	auto& Output = Level == Logging::Level::Error ? std::cerr : std::cout;
	Output << StringStream.str() << std::endl;
}

// -----------------------------------------------------------------------------

} // namespace Logging
} // namespace Utils

// -----------------------------------------------------------------------------

#endif // LOGGING_ENABLED

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
