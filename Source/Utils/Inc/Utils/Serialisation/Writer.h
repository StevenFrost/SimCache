// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

class ISerialisable;

// -----------------------------------------------------------------------------

class Writer
{
public:

	typedef std::string PropertyName;

	virtual bool WriteProperty( const PropertyName& Name, const bool Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const float Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const double Value ) = 0;

	virtual bool WriteProperty( const PropertyName& Name, const int8_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const int16_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const int32_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const int64_t Value ) = 0;

	virtual bool WriteProperty( const PropertyName& Name, const uint8_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const uint16_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const uint32_t Value ) = 0;
	virtual bool WriteProperty( const PropertyName& Name, const uint64_t Value ) = 0;

	virtual bool WriteProperty( const PropertyName& Name, const std::string& Value ) = 0;

	template< class TValue >
	auto WriteProperty( const PropertyName& Name, const TValue& Value ) -> typename std::enable_if< std::is_class< TValue >::value, bool >::type
	{
		static_assert( std::is_base_of< ISerialisable, TValue >::value, "TValue must be a Serialisable type" );

		BeginObject( Name );
		const bool Success = Value.Serialise( *this );
		EndObject();

		return Success;
	}

	template< class TElement >
	auto WriteProperty( const PropertyName& Name, const std::vector< TElement >& Array ) -> typename std::enable_if< std::is_base_of< ISerialisable, TElement >::value, bool >::type
	{
		bool Success = true;

		BeginArray( Name );
		for ( const auto& Element : Array )
		{
			BeginArrayObject();
			Success &= Element.Serialise( *this );
			EndArrayObject();
		}
		EndArray();

		return Success;
	}

	template< class TElement >
	auto WriteProperty( const PropertyName& Name, const std::vector< TElement >& Array ) -> typename std::enable_if< !std::is_base_of< ISerialisable, TElement >::value, bool >::type
	{
		bool Success = true;

		BeginArray( Name );
		for ( const auto& Element : Array )
		{
			Success &= WriteArrayElement( Element );
		}
		EndArray();

		return Success;
	}

	virtual std::string ToString() const = 0;

private:

	virtual void BeginObject( const PropertyName& Name ) = 0;
	virtual void EndObject() = 0;

private:

	virtual void BeginArray( const PropertyName& Name ) = 0;
	virtual void EndArray() = 0;

	virtual void BeginArrayObject() = 0;
	virtual void EndArrayObject() = 0;

	virtual bool WriteArrayElement( const bool Value ) = 0;
	virtual bool WriteArrayElement( const float Value ) = 0;
	virtual bool WriteArrayElement( const double Value ) = 0;

	virtual bool WriteArrayElement( const int8_t Value ) = 0;
	virtual bool WriteArrayElement( const int16_t Value ) = 0;
	virtual bool WriteArrayElement( const int32_t Value ) = 0;
	virtual bool WriteArrayElement( const int64_t Value ) = 0;

	virtual bool WriteArrayElement( const uint8_t Value ) = 0;
	virtual bool WriteArrayElement( const uint16_t Value ) = 0;
	virtual bool WriteArrayElement( const uint32_t Value ) = 0;
	virtual bool WriteArrayElement( const uint64_t Value ) = 0;

	virtual bool WriteArrayElement( const std::string& Value ) = 0;
};

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
