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

	class Reader
	{
	public:

		typedef std::string PropertyName;

		virtual bool ReadProperty( const PropertyName& Name, bool& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, float& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, double& Value ) = 0;

		virtual bool ReadProperty( const PropertyName& Name, int8_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, int16_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, int32_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, int64_t& Value ) = 0;

		virtual bool ReadProperty( const PropertyName& Name, uint8_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, uint16_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, uint32_t& Value ) = 0;
		virtual bool ReadProperty( const PropertyName& Name, uint64_t& Value ) = 0;

		virtual bool ReadProperty( const PropertyName& Name, std::string& Value ) = 0;

		template< class TEnum >
		auto ReadProperty( const PropertyName& Name, TEnum& Value ) -> typename std::enable_if< std::is_enum< TEnum >::value, bool >::type
		{
			typedef typename std::underlying_type< TEnum >::type TEnumType;

			TEnumType EnumValue;
			const bool Success = ReadProperty( Name, EnumValue );
			if ( Success )
			{
				Value = static_cast< TEnum >( EnumValue );
			}

			return Success;
		}

		template< class TValue >
		auto ReadProperty( const PropertyName& Name, TValue& Value ) -> typename std::enable_if< std::is_class< TValue >::value, bool >::type
		{
			static_assert( std::is_base_of< ISerialisable, TValue >::value, "TValue must be derived from ISerialisable" );

			BeginObject( Name );
			const bool Success = Value.Deserialise( *this );
			EndObject();

			return Success;
		}

		template< class TElement >
		auto ReadProperty( const PropertyName& Name, std::vector< TElement >& Array ) -> typename std::enable_if< std::is_base_of< ISerialisable, TElement >::value, bool >::type
		{
			bool Success = true;

			BeginArray( Name );

			const size_t ArraySize = GetArraySize();

			Array.clear();
			Array.resize( ArraySize );

			for ( size_t Index = 0; Index < ArraySize; ++Index )
			{
				BeginArrayObject( Index );
				Success &= Array[ Index ].Deserialise( *this );
				EndArrayObject();
			}

			EndArray();

			return Success;
		}

		template< class TElement >
		auto ReadProperty( const PropertyName& Name, std::vector< TElement >& Array ) -> typename std::enable_if< !std::is_base_of< ISerialisable, TElement >::value, bool >::type
		{
			bool Success = true;

			BeginArray( Name );

			const size_t ArraySize = GetArraySize();

			Array.clear();
			Array.resize( ArraySize );

			for ( size_t Index = 0; Index < ArraySize; ++Index )
			{
				BeginArrayObject( Index );
				Success &= ReadArrayElement( Array[ Index ] );
				EndArrayObject();
			}

			EndArray();

			return Success;
		}

	private:

		virtual void BeginObject( const PropertyName& Name ) = 0;
		virtual void EndObject() = 0;

	private:

		virtual size_t GetArraySize() const = 0;

		virtual void BeginArray( const PropertyName& Name ) = 0;
		virtual void EndArray() = 0;

		virtual void BeginArrayObject( const size_t Index ) = 0;
		virtual void EndArrayObject() = 0;

		virtual bool ReadArrayElement( bool& Value ) = 0;
		virtual bool ReadArrayElement( float& Value ) = 0;
		virtual bool ReadArrayElement( double& Value ) = 0;

		virtual bool ReadArrayElement( int8_t& Value ) = 0;
		virtual bool ReadArrayElement( int16_t& Value ) = 0;
		virtual bool ReadArrayElement( int32_t& Value ) = 0;
		virtual bool ReadArrayElement( int64_t& Value ) = 0;

		virtual bool ReadArrayElement( uint8_t& Value ) = 0;
		virtual bool ReadArrayElement( uint16_t& Value ) = 0;
		virtual bool ReadArrayElement( uint32_t& Value ) = 0;
		virtual bool ReadArrayElement( uint64_t& Value ) = 0;

		virtual bool ReadArrayElement( std::string& Value ) = 0;
	};

	// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
