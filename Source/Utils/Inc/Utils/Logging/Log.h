// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <cstdint>
#include <string>

// -----------------------------------------------------------------------------

#define LOG( CategoryName, CategoryLevel, Message, ... ) g_traceArea##CategoryName.Output( Utils::Logging::Level::CategoryLevel, Message, ##__VA_ARGS__ );

#define DECLARE_LOG_CATEGORY( CategoryName ) extern Utils::Logging::Category g_traceArea##CategoryName;
#define DEFINE_LOG_CATEGORY( CategoryName, CategoryLevel ) Utils::Logging::Category g_traceArea##CategoryName( #CategoryName, Utils::Logging::Level::CategoryLevel );

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

	const std::string& GetName() const;
	Level GetLevel() const;

private:

	const std::string	CategoryName;
	const Level			CategoryLevel;
};

// -----------------------------------------------------------------------------

} // namespace Logging
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
