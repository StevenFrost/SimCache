// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Serialisation/Reader.h>

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#include <stack>
#include <utility>

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

class JSONReader
	: public Reader
{
public:

	JSONReader( const std::string& Data );

public:

	virtual bool ReadProperty( const PropertyName& Name, bool& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, float& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, double& Value ) override final;

	virtual bool ReadProperty( const PropertyName& Name, int8_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, int16_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, int32_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, int64_t& Value ) override final;

	virtual bool ReadProperty( const PropertyName& Name, uint8_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, uint16_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, uint32_t& Value ) override final;
	virtual bool ReadProperty( const PropertyName& Name, uint64_t& Value ) override final;

	virtual bool ReadProperty( const PropertyName& Name, std::string& Value ) override final;

private:

	virtual void BeginObject( const PropertyName& Name ) override final;
	virtual void EndObject() override final;

private:

	virtual size_t GetArraySize() const override final;

	virtual void BeginArray( const PropertyName& Name ) override final;
	virtual void EndArray() override final;

	virtual void BeginArrayObject( const size_t Index ) override final;
	virtual void EndArrayObject() override final;

	virtual bool ReadArrayElement( bool& Value ) override final;
	virtual bool ReadArrayElement( float& Value ) override final;
	virtual bool ReadArrayElement( double& Value ) override final;

	virtual bool ReadArrayElement( int8_t& Value ) override final;
	virtual bool ReadArrayElement( int16_t& Value ) override final;
	virtual bool ReadArrayElement( int32_t& Value ) override final;
	virtual bool ReadArrayElement( int64_t& Value ) override final;

	virtual bool ReadArrayElement( uint8_t& Value ) override final;
	virtual bool ReadArrayElement( uint16_t& Value ) override final;
	virtual bool ReadArrayElement( uint32_t& Value ) override final;
	virtual bool ReadArrayElement( uint64_t& Value ) override final;

	virtual bool ReadArrayElement( std::string& Value ) override final;

private:

	std::string GetCurrentPath() const;

	rapidjson::Value* GetCurrentObject();
	const rapidjson::Value* GetCurrentObject() const;

	rapidjson::Value* GetMember( const PropertyName& Name );

private:

	typedef std::string PathName;
	typedef std::pair< PathName, rapidjson::Pointer > NamedPointer;

	rapidjson::Document			JsonDocument;
	std::stack< NamedPointer >	Stack;
};

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
