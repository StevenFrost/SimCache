// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <cstdint>
#include <string>

// -----------------------------------------------------------------------------

#ifdef LOGGING_ENABLED
#define LOG( CategoryName, CategoryLevel, Message, ... ) g_traceArea##CategoryName.Output( Utils::Logging::Level::CategoryLevel, Message, ##__VA_ARGS__ );

#define DECLARE_LOG_CATEGORY( CategoryName ) extern Utils::Logging::Category g_traceArea##CategoryName;
#define DEFINE_LOG_CATEGORY( CategoryName, CategoryLevel ) Utils::Logging::Category g_traceArea##CategoryName( #CategoryName, Utils::Logging::Level::CategoryLevel );
#else
#define LOG( CategoryName, CategoryLevel, Message, ... )

#define DECLARE_LOG_CATEGORY( CategoryName )
#define DEFINE_LOG_CATEGORY( CategoryName, CategoryLevel )
#endif // LOGGING_ENABLED

// -----------------------------------------------------------------------------

#ifdef LOGGING_ENABLED

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Logging
{

// -----------------------------------------------------------------------------

enum class Level : uint8_t
{
	Error,
	Warning,
	Info,
	Verbose,
	Default
};

// -----------------------------------------------------------------------------

class Category
{
public:

	Category( const std::string& CategoryName, const Level CategoryLevel );

	void Output( Level Level, std::string Message, ... );

private:

	void OutputInternal( const Level Level, const std::string& Message, va_list Args );

private:

	const std::string	CategoryName;
	const Level			CategoryLevel;
};

// -----------------------------------------------------------------------------

} // namespace Logging
} // namespace Utils

// -----------------------------------------------------------------------------

#endif // LOGGING_ENABLED

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
